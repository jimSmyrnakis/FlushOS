#ifndef __FAT16_COMMON_C__
#define __FAT16_COMMON_C__

    #include "fat16.h"
    

    // all common static functions are here , i find that very usefull 
    // for hiding these symbols from the final kernel full object file
    // espacially if it will be used for the drivers in the future :)

    static void release_private_data(struct fat16_private* priv){
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

    struct file_system fat16_fs = {
        .open = fat16_open,
        .resolve = fat16_resolve,
        .read = fat16_read
    };

    uint32_t cluster_get_info(
        uint32_t cluster ,
        struct disk* disk ,
        uint32_t* cluster_sector ,
        uint32_t* cluster_bytes , 
        uint32_t* cluster_sectors){
        struct fat16_private* priv = disk->priv;
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

    #include "load_item_from_disk.c"

#endif 