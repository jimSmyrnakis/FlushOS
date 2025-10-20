#ifndef __FLUSHOS_FAT16_OPEN_DESCRIPTOR_GET_ITEM_C__
#define __FLUSHOS_FAT16_OPEN_DESCRIPTOR_GET_ITEM_C__
    #include "common.c"
    #include "find_item_in_directory.c"

    void fat16_free_item(struct fat16_item* item){
        if (item->type == FAT16_FILE_TYPE_DIRECTORY)
        {
            fat16_free_directory(item->directory);
            
        }
        
        kfree(item);
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

#endif 