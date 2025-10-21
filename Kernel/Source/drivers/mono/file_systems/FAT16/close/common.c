#ifndef __FLUSHOS_FAT16_CLOSE_COMMON_C__
#define __FLUSHOS_FAT16_CLOSE_COMMON_C__

    #include "inc.h"
    #include "../common.c"
    
    void fat16_free_fat16_descriptor(struct fat16_descriptor* desc){
        if (!desc ) return ;

        fat16_free_item(desc->item);
        kfree(desc);
    }

#endif 