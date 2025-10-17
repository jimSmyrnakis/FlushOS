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
        .resolve = fat16_resolve
    };

#endif 