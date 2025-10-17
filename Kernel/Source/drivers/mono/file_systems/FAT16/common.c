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

    struct file_system fat16_fs = {
        .open = fat16_open,
        .resolve = fat16_resolve
    };

#endif 