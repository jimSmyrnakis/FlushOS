#ifndef __FAT16_INIT_PRIVATE_C__
#define __FAT16_INIT_PRIVATE_C__

    #include "inc.h"
    #include "common.c"
    #include "get_root_dirs.c"
    
    static errno init_fat16_private(struct fat16_private** priv_dptr , struct disk* disk){
        

        // init parameter return ptr
        (*priv_dptr) = NULL;

        struct fat16_private* priv = 
        (struct fat16_private*) kzalloc(sizeof(struct fat16_private));
        // check if allocation succeded
        if (priv == NULL)
            return FLUSHOS_ENOMEM;
        // we know 2 things either the header is still exist's in 0x7c00 but 
        // that may not good to use especially with all others data for cpu 
        // like gdt , ldt , idt and more . Nothing guaranteed that for us , 
        // so we must read the first sector from the disk .
        char* boot_sector = (char*)kzalloc(sizeof(disk->sector_size));
        if (boot_sector == NULL){

            kfree(priv);
            return FLUSHOS_ENOMEM;

        }

        // read the first sector of this disk (real or virtual)
        errno res = disk->read_function(0 , 1 , boot_sector);
        if (res != FLUSHOS_EGOOD){
            kfree(priv);
            return res;
        }

        // now copy the right bytes to our headers  
        memcpy( &priv->header.bios_parameter_block , boot_sector , sizeof(struct fat16_bpb));
        memcpy( &priv->header.extended_bios_parameter_block , 
            &boot_sector[sizeof(struct fat16_bpb)] , sizeof(struct fat16_ebpb));
        // we don't need any more the first sector 
        kfree(boot_sector);

        priv->data_stream = disk_stream_create(disk->id);
        if (priv->data_stream == NULL){
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }

        priv->FAT_stream = disk_stream_create(disk->id);
        if (priv->FAT_stream == NULL){
            disk_stream_destroy(priv->data_stream);
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }


        res = init_fat16_private_root_directory(priv , disk);
        if (res != FLUSHOS_EGOOD){
            disk_stream_destroy(priv->data_stream);
            disk_stream_destroy(priv->FAT_stream);
            kfree(priv);
            return res;
        }


        // set the result pointer 
        (*priv_dptr) = priv;
        return FLUSHOS_EGOOD;
    }


#endif 