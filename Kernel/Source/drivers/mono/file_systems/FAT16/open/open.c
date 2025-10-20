#ifndef __FLUSHOS_FAT16_OPEN_C__
#define __FLUSHOS_FAT16_OPEN_C__

    #include "common.c"
    #include "descriptor_get_item.c"

    

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



#endif 