#include "fat16.h"
#include "fat16_structs.h"
#include <std/string.h>
#include <stdbool.h>
#include <config.h>
#include "common.h"
struct file_system fat16_fs = {
        .open = fat16_open,
        .resolve = fat16_resolve,
        .read = fat16_read ,
        .seek = fat16_seek ,
        .stat = fat16_stat ,
        .close = fat16_close
    };


struct file_system* fat16_init(void){
    strncpy( fat16_fs.name  , "FAT16" , 6);

    return &fat16_fs;
}
    struct fat16_item* fat16_find_item_in_directory(
        struct disk* disk, 
        struct fat16_directory* dir, 
        struct path_part* part
    ){ // the dir must fully loaded and the return item will loaded from us
        // if no part given return nULL
        if (part == NULL){
            return NULL;
        }

        // 


        // is the part target in the current directory ?

        uint32_t i = 0;
        while( i < dir->count ){
            // now read each item 
            char tmp_filename[KERNEL_MAX_PATH_SIZE];
            fat16_get_full_relative_filename(&dir->directory_items[i], tmp_filename, sizeof(tmp_filename));
            int cmp = istrncmp( 
                (const char*)tmp_filename , 
                (const char*)part->part , sizeof(tmp_filename));

            if (cmp == 0){
                // found it 
                break;
            }

            i++;
        }

        // if not found return NULL
        if (i >= dir->count)    return NULL;

        //else we found it and must now load from the disk all it's parts
        struct fat16_item* new_item = fat16_load_item_from_disk(
            disk , 
            &dir->directory_items[i]);
        
        
        if (new_item == NULL){
            return NULL;
        }
        

        

        return new_item;
    }

    struct fat16_item* fat16_descriptor_get_item(struct disk* disk , struct path_part* part){
        

        struct fat16_private* priv = disk->priv;


        struct fat16_item* root_item 
            = fat16_find_item_in_directory(disk, &priv->root_directory, part);
        if (!root_item)
        {
            return NULL;
        }
        struct path_part* cpart = part->next;
        struct fat16_item* citem = root_item;
        struct fat16_item* pitem = NULL;
        while (cpart != NULL)
        {
            citem = 
            fat16_find_item_in_directory(disk , &citem->directory , cpart );
            if (pitem != root_item)
                fat16_free_item(pitem);
            pitem = citem;
            if (citem == NULL){
                return NULL;
            }
            
            cpart = cpart->next;
        }
        
        




        return citem;
    }

    void fat16_free_fat16_descriptor(struct fat16_descriptor* desc){
        if (!desc ) return ;

        fat16_free_item(desc->item);
        kfree(desc);
    }

    bool is_fat16_header(struct fat16_header header){
        bool check = 
        (header.bios_parameter_block.fat_copies == 1) || 
        (header.bios_parameter_block.fat_copies);

        check = check && 
        (
            (header.extended_bios_parameter_block.signature == 0x29) ||
            (header.extended_bios_parameter_block.signature == 0x28)
        );

        

        return check;
    } 

    void release_private_data(struct fat16_private* priv){
        if (priv == NULL)
            return ;

        if (priv->data_stream)
            disk_stream_destroy(priv->data_stream);

    
    }

    void fat16_free_directory(struct fat16_directory dir){
        if (dir.directory_items)
            kfree(dir.directory_items);

        
    }

    void fat16_to_proper_string(char** out, const char* in)
    {
        while(*in != 0x00 && *in != 0x20)
        {
            **out = *in;
            *out += 1;
            in +=1;
        }

        if (*in == 0x20)
        {
            **out = 0x00;
        }
    }


    void fat16_get_full_relative_filename(struct fat16_directory_item* item, char* out, int max_len)
    {
        memset(out, 0x00, max_len);
        char *out_tmp = out;
        fat16_to_proper_string(&out_tmp, (const char*) item->filename);
        if (item->ext[0] != 0x00 && item->ext[0] != 0x20)
        {
            *out_tmp++ = '.';
            fat16_to_proper_string(&out_tmp, (const char*) item->ext);
        }

    }

    

    uint32_t cluster_get_info(
        uint32_t cluster ,
        struct disk* disk ,
        uint32_t* cluster_sector ,
        uint32_t* cluster_bytes , 
        uint32_t* cluster_sectors){
        struct fat16_private* priv = (struct fat16_private*)disk->priv;
        uint32_t first_data_sector = priv->header.bios_parameter_block.reserved_sectors;
        first_data_sector += 
            priv->header.bios_parameter_block.fat_copies *
            priv->header.bios_parameter_block.sectors_per_fat;

        uint32_t root_sectors = (priv->header.bios_parameter_block.root_dir_entries 
            * sizeof(struct fat16_directory_item) );
        first_data_sector += 
             root_sectors / disk->sector_size;
        if (root_sectors % disk->sector_size){
            first_data_sector++;
        }
        uint32_t sector_per_cluster = priv->header.bios_parameter_block.sectors_per_cluster;
        uint32_t cluster_first_sector = first_data_sector + (cluster - 2) * sector_per_cluster ;

        uint32_t bytes_total = sector_per_cluster * disk->sector_size;

        (*cluster_sector) = cluster_first_sector;
        (*cluster_bytes) = bytes_total;
        (*cluster_sectors) = sector_per_cluster;
        return cluster_first_sector;
    }

    bool fat16_is_cluster_used(fat16_entry cluster){
        // last sector 
            if (cluster == 0xFF8 || cluster == 0xFFF){
                return false;
            }
            // Reserved sector?
            if (cluster == 0xFF0 || cluster == 0xFF6)
            {
                return false;
            }
            // wtf sector ?
            if (cluster == 0x00){
                return false;
            }

            return true;
    }

    uint32_t fat16_get_cluster_from_directory_item(struct fat16_directory_item* item){
        return item->high_16_bits_first_cluster << 16 | item->low_16_bits_first_cluster;
    }

    void fat16_free_item(struct fat16_item* item){
        if (item->type == FAT16_FILE_TYPE_DIRECTORY)
        {
            fat16_free_directory(item->directory);
            
        }
        
        kfree(item);
    }

    void* fat16_read_data_cluster(struct disk* disk , fat16_entry cluster , uint32_t count){
        if ( (disk == NULL) || (cluster <= 1) || (count == 0))
            return NULL;

        

        struct fat16_private* priv = (struct fat16_private*)disk->priv;
        //FirstDataSector = ReservedSectorCount 
        //        + (NumFATs * FATSize)
        //        + RootDirSectors

        uint32_t cluster_first_sector ;
        uint32_t sectors_per_cluster;
        uint32_t bytes_total ;
        cluster_get_info(cluster , disk , &cluster_first_sector , &bytes_total , &sectors_per_cluster);
        uint8_t* data_cluster = (uint8_t*)kzalloc(count * bytes_total);
        if (data_cluster == NULL)   return NULL;
 
        // based on the fat table FAT1 load every cluster

        fat16_entry current_cluster = cluster ;
        fat16_entry next_cluster ;
        for (uint32_t i = 0;  i < count ; i++){
            // for each cluster 
            
            errno res = 
            disk_read_sector(
                disk  , cluster_first_sector , 
                sectors_per_cluster , data_cluster + bytes_total * i );
            if (res != FLUSHOS_EGOOD){
                kfree(data_cluster);
                return NULL;
            }
            current_cluster = priv->FAT1[cluster];
            if (fat16_is_cluster_used(current_cluster) == false){
                break;
            }
        }

        

        return data_cluster;
        
    }



    struct fat16_item* fat16_load_item_from_disk( // this method supports only one cluster for moment
        struct disk* disk ,
        struct fat16_directory_item* item){
        if (item == NULL)
            return NULL;

        // take all private data (the struct we use)
        struct fat16_private* priv = (struct fat16_private*)disk->priv;

        struct fat16_item* new_item = (struct fat16_item*)kzalloc(sizeof(struct fat16_item));
        if (new_item == NULL)
            return NULL;
        // now everything we need is here 
        if (item->attribute & FAT16_ATTRIBUTE_DIRECTORY){
            // if is directory load that otherwise load nothing
            // the new item is this item struct 
            
            new_item->type = FAT16_FILE_TYPE_DIRECTORY;
            
            // load from disk one cluster , first found all used ones
            uint32_t first_cluster = 
            item->low_16_bits_first_cluster & (item->high_16_bits_first_cluster << 16);
            // find all data clusters of this directory 
            fat16_entry current_cluster = first_cluster;
            uint32_t cluster_count = 1;
            while(fat16_is_cluster_used(current_cluster)){
                cluster_count++;
                current_cluster = priv->FAT1[current_cluster];
            }
            void* cluster = fat16_read_data_cluster(disk , first_cluster , cluster_count);
            new_item->directory.directory_items = (struct fat16_directory_item*)cluster;
            int cnt = 0;
            while(new_item->directory.directory_items[cnt].filename != 0x00){
                cnt++;
            }
            new_item->directory.count = cnt;
        }
        else {
            new_item->type = FAT16_FILE_TYPE_SIMPLE_FILE;
            memcpy(&new_item->file , item , sizeof(*item));
        }



        return new_item;
    }


    errno get_root_items(struct fat16_private* priv , struct disk* disk){

        uint32_t max_items = priv->header.bios_parameter_block.root_dir_entries;
        priv->root_directory.count = 0;

        // create one item unit for reading to it
        struct fat16_directory_item item ;
        memset(&item , 0x00 , sizeof(item));

        // now just for convinience make a short cut name for the stream
        struct disk_stream stream = *priv->root_stream;

        // take the first sector for our root directory
        uint32_t root_dir_first_sector = 
            priv->header.bios_parameter_block.reserved_sectors + 
            (priv->header.bios_parameter_block.fat_copies *
             priv->header.bios_parameter_block.sectors_per_fat);

        // now just make it point to the first byte 
        disk_stream_seek(&stream  , SEEK_SET , 
        root_dir_first_sector * disk->sector_size);

        // let's try read every single item 
        uint32_t item_count = 0;
        while (item_count < max_items)
        {
            errno res = disk_stream_read(&stream , &item , sizeof(item));
            if (res != FLUSHOS_EGOOD){
                return res;
            }

            // is it last ?
            if (item.filename[0] == 0x00){
                break;
            }

            // is it unused ? then don't count it
            if (item.filename[0] == 0xE5){
                continue;
            }

            item_count ++;
        }
        

        priv->root_directory.count = item_count;
        
        // load all items
        priv->root_directory.directory_items = kzalloc(max_items * sizeof(item));
        uint32_t i  = 0;
        struct disk_stream stream2 = *priv->root_stream;
        while (i < max_items)
        {
            errno res = disk_stream_read(&stream2 , &item  , sizeof(item));
            if (res != FLUSHOS_EGOOD){
                return res;
            }
            memcpy(&priv->root_directory.directory_items[i] , &item , sizeof(item));
            // is it last ?
            if (item.filename[0] == 0x00){
                break;
            }

            // is it unused ? then don't count it
            if (item.filename[0] == 0xE5){
                continue;
            }

            i ++;
        }
        return FLUSHOS_EGOOD;
    }


    errno init_fat16_private_root_directory(struct fat16_private* priv , struct disk* disk){
        // first we set that header of fat16 is loaded and everything else except root dirs
        
        // A root directory is nothing else that a unamed folder that is the beggining 
        // of our file system and is responsible for showing us the first files/directories
        // .
        // Headers (bpb,ebpb) + Bootloader (first sector)
        // Reseved Sectors (described by the bpb , ebpb)
        // FAT1,
        // FAT2(optional)
        // Root dir (a list of items where the count is defined in the headers)
        // Data Clusters (dirs/drivers/files all here - Clusters 0,1 are for special puprose)
        // Yes the size of a cluster , how many reseved sectors , how many each sectors fat 
        // is taken , if FAT2 exist's (is just a backup) , how many items (root files/dirs/drivers)
        // are in root dir all of them are in the headers . Headers (bpb,ebpb) have signature and
        // expected values that they define fat16 format and some hardware info that may filled in from 
        // bios , still do not trust them , ask the hardware it self always not expect everything from
        // bios .  

        // take the first sector for our root directory
        uint32_t root_dir_first_sector = 
            priv->header.bios_parameter_block.reserved_sectors + 
            (priv->header.bios_parameter_block.fat_copies *
             priv->header.bios_parameter_block.sectors_per_fat);

        // short name for the number of items in the root (x:/ is always refers to the 
        // root folder so we must be carefull and always save the new items back )
        uint32_t root_dir_entries = priv->header.bios_parameter_block.root_dir_entries;

        // how many bytes the root dir has ?
        uint32_t root_dir_size = root_dir_entries * sizeof(struct fat16_directory_item);

        // now find the total number of sectors required for them
        uint32_t total_sectors = root_dir_size / disk->sector_size;
        if (root_dir_size % disk->sector_size){
            total_sectors ++;
        }

        // initiallize our streams to point in the right place

        errno res;

        // now data stream is after the last sector of the root dir
        res = disk_stream_seek(priv->data_stream , SEEK_SET , 
            (root_dir_first_sector + total_sectors) * disk->sector_size);
        if (res != FLUSHOS_EGOOD){
            return res;
        }

        //the root stream 
        res = disk_stream_seek(priv->root_stream , SEEK_SET , 
        root_dir_first_sector * disk->sector_size);
        if (res != FLUSHOS_EGOOD){
            return res;
        }

        // finally just caculate the first and last sector for our root directory
        priv->root_directory.first_sector = root_dir_first_sector;
        priv->root_directory.last_sector = root_dir_first_sector + total_sectors;
        
        // we define streams position in bytes , so be carefull caculate only sector number 
        // is wrong

        return FLUSHOS_EGOOD;
    }

    errno init_fat16_private(struct fat16_private** priv_dptr , struct disk* disk){
        

        // init parameter return ptr
        (*priv_dptr) = NULL;

        struct fat16_private* priv = 
        (struct fat16_private*) kzalloc(sizeof(struct fat16_private));
        // check if allocation succeded
        if (priv == NULL)
            return FLUSHOS_ENOMEM;
        // we know 2 things either the header is still exist's in 0x7c00 but 
        // that may not good to use especially with all others data for cpu 
        // like gdt , ldt , idt and more . Nothing guaranteed that for us , 
        // so we must read the first sector from the disk .

        // first allocate some memory blocks
        char* boot_sector = (char*)kzalloc(sizeof(disk->sector_size));
        if (boot_sector == NULL){

            kfree(priv);
            return FLUSHOS_ENOMEM;

        }

        // read the first sector of this disk (real or virtual-partitioned)
        errno res = disk->read_function(0 , 1 , boot_sector);
        if (res != FLUSHOS_EGOOD){
            kfree(priv);
            return res;
        }

        // now copy the right bytes to our headers that represents these system structs
        memcpy( &priv->header.bios_parameter_block , boot_sector , sizeof(struct fat16_bpb));
        memcpy( &priv->header.extended_bios_parameter_block , 
            &boot_sector[sizeof(struct fat16_bpb)] , sizeof(struct fat16_ebpb));
        // we don't need any more the first sector 
        kfree(boot_sector);

        // This header must be put into the test , this header 
        // defines that disk is formated with fat16 or something else
        if (is_fat16_header(priv->header) == false){
            kfree(priv);
            return FLUSHOS_EFSNOTUS;
        }
        // nice everything is tested (i want to believe at least) 
        // so now just fill our structs :)

        // Create a data stream for our data cluster's
        priv->data_stream = disk_stream_create(disk->id);
        if (priv->data_stream == NULL){
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }

        // Load FAT1/2 Tables
        uint32_t FAT_total_sectors = priv->header.bios_parameter_block.sectors_per_fat;
        uint32_t FAT_total_size = disk->sector_size * FAT_total_sectors;
        uint32_t FAT1_first_sector = priv->header.bios_parameter_block.reserved_sectors;
        uint32_t FAT2_first_sector = FAT1_first_sector + priv->header.bios_parameter_block.sectors_per_fat;
        priv->FAT1 = kzalloc(sizeof(fat16_entry) * FAT_total_size);
        if (priv->FAT1 == NULL)
        {
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }
        disk->read_function(FAT1_first_sector , FAT_total_sectors , priv->FAT1);
        if (priv->header.bios_parameter_block.fat_copies == 2){
            priv->FAT2 = kzalloc(sizeof(fat16_entry) * FAT_total_size);
            if (priv->FAT2 == NULL){
                kfree(priv);
                kfree(priv->FAT1);
                return FLUSHOS_ENOMEM;
            }
            disk->read_function(FAT2_first_sector , FAT_total_sectors , priv->FAT2);
        }
        

        // create a root stream
        priv->root_stream = disk_stream_create(disk->id);
        if (priv->root_stream == NULL){
            disk_stream_destroy(priv->data_stream);
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }

        // data and FAT streams are very important , they need to be updated constantly
        // 


        res = init_fat16_private_root_directory(priv , disk);
        if (res != FLUSHOS_EGOOD){
            disk_stream_destroy(priv->data_stream);
            disk_stream_destroy(priv->root_stream);
            kfree(priv);
            return res;
        }

        // now we want to find all existed directories/file (or general items) 
        // we now only the maximum number of available item "slots" but not 
        // how many of them are used . We can see tho that our file system driver
        // is initiallize it's behavor in the resolve method :) . So the best we need to 
        // do is just cache the root item's structs (not data cluster's ) and everything 
        // we might use in the rest methods :) , like the bpb,ebpb headers , FAT1,FAT2 .
        res = get_root_items(priv , disk );
        if (res != FLUSHOS_EGOOD){
            disk_stream_destroy(priv->data_stream);
            disk_stream_destroy(priv->root_stream);
            kfree(priv);
            return res;
        }



        // set the result pointer 
        (*priv_dptr) = priv;
        return FLUSHOS_EGOOD;
    }




    errno fat16_stat(struct disk* disk, void* private , struct file_stat* stat){
        
        struct fat16_descriptor* descr = (struct fat16_descriptor* )private;
        if (descr->item->type != FAT16_FILE_TYPE_SIMPLE_FILE){
            return FLUSHOS_INVLDIO;
        }

        strncpy( stat->name , (const char*)descr->item->file.filename , KERNEL_MAX_FILE_NAME_SIZE);
        if (descr->item->file.attribute & FAT16_ATTRIBUTE_READ_ONLY){
            stat->status |= FILE_STATUS_READ_ONLY;
        }

        stat->size = descr->item->file.filesize;

        return FLUSHOS_EGOOD;
    }



    errno fat16_seek(void* private, int offset, enum seek_mode seek_mode){
        
        struct fat16_descriptor* descr = (struct fat16_descriptor* )private;
        if (descr->item->type != FAT16_FILE_TYPE_SIMPLE_FILE){
            return FLUSHOS_INVLDIO;
        }

        if (offset >= (int32_t)descr->item->file.filesize){
            return FLUSHOS_EBADARG;
        }

        switch(seek_mode){
            case SEEK_CUR: descr->pos += offset; break;
            case SEEK_END: return FLUSHOS_ENIMPL;
            case SEEK_SET: descr->pos = offset; break;
            default:
                return FLUSHOS_EBADARG;
        }
        

        return FLUSHOS_EGOOD;
    }


    errno fat16_resolve(struct disk* disk){
        //check if disk is good parameter
        if (disk == NULL)
            return FLUSHOS_EBADARG;

        struct fat16_private* priv = NULL;
        errno res = init_fat16_private(&priv , disk);
        if (priv == NULL){
            return res;
        }

        

        disk->priv = priv;
        disk->fs = &fat16_fs;

        return FLUSHOS_EGOOD;
    }

    
    errno fat16_read(
        struct disk* disk, 
        void* private, 
        uint32_t size, 
        uint32_t nmemb, 
        char* out){

        
        //dsfasaf
        struct fat16_descriptor* descr = (struct fat16_descriptor*)private;

        uint32_t cluster_sectors = 0 , cluster_first_sector = 0, cluster_bytes = 0 ;
        uint32_t first_file_cluster = fat16_get_cluster_from_directory_item(&descr->item->file);
        // 
        cluster_get_info( first_file_cluster
        , disk , &cluster_first_sector , &cluster_bytes  , &cluster_sectors);

        // amount of clusters
        uint32_t clusters_amount = (size * nmemb ) / cluster_bytes;
        if ((size * nmemb ) % cluster_bytes) clusters_amount++;
        // so we need that many clusters at least;

        // Now witch one is the first one cluster we will need
        uint32_t clusters_offset = descr->pos / cluster_bytes;
        void* clusters_data = 
        fat16_read_data_cluster(disk , first_file_cluster + clusters_offset , clusters_amount);
        if (clusters_data == NULL)
            return FLUSHOS_ENOMEM;

        // now we have all clusters data we need the in cluster offset based on pos
        uint32_t in_cluster_offset = descr->pos % cluster_bytes;
        
        // copy the result in the output 
        memcpy(out ,  clusters_data + in_cluster_offset , size * nmemb);

        // This implementation is the simples't one (no caching clusters)
        // no write through or write back logic , slow and simple
        descr->pos += size * nmemb;
        return FLUSHOS_EGOOD;
    } 



    void* fat16_open(struct disk* disk, struct path_part * part, file_mode bit_mode){

        struct fat16_descriptor* descr = 
        (struct fat16_descriptor*)kzalloc(sizeof(struct fat16_descriptor));
        if (descr == NULL)
            return NULL;

        
        //fdfsad
        descr->item = fat16_descriptor_get_item(disk , part);
        if (descr->item == NULL){
            kfree(descr);
            return NULL;
        }
        descr->pos = 0;


        // not implemented yet
        return descr;
    }

    errno fat16_close(void* private ){
        
        struct fat16_descriptor* descr = (struct fat16_descriptor* )private;
        if (!descr){
            return FLUSHOS_INVLDIO;
        }

        
        fat16_free_fat16_descriptor(descr);


        return FLUSHOS_EGOOD;
    }
    

    





