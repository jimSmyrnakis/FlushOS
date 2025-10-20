#ifndef __FLUSHOS_FAT16_OPEN_FIND_ITEM_IN_DIRECTORY_C__
#define __FLUSHOS_FAT16_OPEN_FIND_ITEM_IN_DIRECTORY_C__

    #include "common.c"
    #include "../../../../../std/string.h"
    #include "../../../../../config.h"

    

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
            int cmp = istrncmp( 
                (const char*)dir->directory_items->filename , 
                (const char*)part->part , KERNEL_MAX_PATH_PART_SIZE);

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
#endif 