#ifndef __FLUSHOS_FAT16_LOAD_ITEM_FROM_DISK_C__
#define __FLUSHOS_FAT16_LOAD_ITEM_FROM_DISK_C__

    #include "fat16.h"
    #include "open/inc.h"
    #include "read_data_clusters.c"
    // for a simple / special file just load it as is , for a directory load all its
    // clusters too . We don't do anything special with other files
    struct fat16_item* fat16_load_item_from_disk( // this method supports only one cluster for moment
        struct disk* disk ,
        struct fat16_directory_item* item){
        if (item == NULL)
            return NULL;

        // take all private data (the struct we use)
        struct fat16_private* priv = disk->priv;

        struct fat16_item* new_item = kzalloc(sizeof(struct fat16_item));
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

#endif 