
// be sure to include that only once in the final file

#ifndef __FAT16_RESOLVE_C__
#define __FAT16_RESOLVE_C__

    #include "inc.h"

    #include "init_private.c"
    #include "../common.c"
    
    
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

#endif 