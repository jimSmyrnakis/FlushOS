#ifndef __FLUSHOS_FAT16_RESOLVE_GET_ROOT_ITEMS_C__
#define __FLUSHOS_FAT16_RESOLVE_GET_ROOT_ITEMS_C__

    #include "inc.h"
    #include "common.c"

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

#endif 