#ifndef __FAT16_INIT_PRIVATE_C__
#define __FAT16_INIT_PRIVATE_C__

    #include "inc.h"
    #include "common.c"
    #include "get_root_dirs.c"
    #include "get_root_items.c"
    
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

        // first allocate some memory blocks
        char* boot_sector = (char*)kzalloc(sizeof(disk->sector_size));
        if (boot_sector == NULL){

            kfree(priv);
            return FLUSHOS_ENOMEM;

        }

        // read the first sector of this disk (real or virtual-partitioned)
        errno res = disk->read_function(0 , 1 , boot_sector);
        if (res != FLUSHOS_EGOOD){
            kfree(priv);
            return res;
        }

        // now copy the right bytes to our headers that represents these system structs
        memcpy( &priv->header.bios_parameter_block , boot_sector , sizeof(struct fat16_bpb));
        memcpy( &priv->header.extended_bios_parameter_block , 
            &boot_sector[sizeof(struct fat16_bpb)] , sizeof(struct fat16_ebpb));
        // we don't need any more the first sector 
        kfree(boot_sector);

        // This header must be put into the test , this header 
        // defines that disk is formated with fat16 or something else
        if (is_fat16_header(priv->header) == false){
            kfree(priv);
            return FLUSHOS_EFSNOTUS;
        }
        // nice everything is tested (i want to believe at least) 
        // so now just fill our structs :)

        // Create a data stream for our data cluster's
        priv->data_stream = disk_stream_create(disk->id);
        if (priv->data_stream == NULL){
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }

        // Load FAT1/2 Tables
        uint32_t FAT_total_sectors = priv->header.bios_parameter_block.sectors_per_fat;
        uint32_t FAT_total_size = disk->sector_size * FAT_total_sectors;
        uint32_t FAT1_first_sector = priv->header.bios_parameter_block.reserved_sectors;
        uint32_t FAT2_first_sector = FAT1_first_sector + priv->header.bios_parameter_block.sectors_per_fat;
        priv->FAT1 = kzalloc(sizeof(fat16_entry) * FAT_total_size);
        if (priv->FAT1 == NULL)
        {
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }
        disk->read_function(FAT1_first_sector , FAT_total_sectors , priv->FAT1);
        if (priv->header.bios_parameter_block.fat_copies == 2){
            priv->FAT2 = kzalloc(sizeof(fat16_entry) * FAT_total_size);
            if (priv->FAT2 == NULL){
                kfree(priv);
                kfree(priv->FAT1);
                return FLUSHOS_ENOMEM;
            }
            disk->read_function(FAT2_first_sector , FAT_total_sectors , priv->FAT2);
        }
        

        // create a root stream
        priv->root_stream = disk_stream_create(disk->id);
        if (priv->root_stream == NULL){
            disk_stream_destroy(priv->data_stream);
            kfree(priv);
            return FLUSHOS_ENOMEM;
        }

        // data and FAT streams are very important , they need to be updated constantly
        // 


        res = init_fat16_private_root_directory(priv , disk);
        if (res != FLUSHOS_EGOOD){
            disk_stream_destroy(priv->data_stream);
            disk_stream_destroy(priv->root_stream);
            kfree(priv);
            return res;
        }

        // now we want to find all existed directories/file (or general items) 
        // we now only the maximum number of available item "slots" but not 
        // how many of them are used . We can see tho that our file system driver
        // is initiallize it's behavor in the resolve method :) . So the best we need to 
        // do is just cache the root item's structs (not data cluster's ) and everything 
        // we might use in the rest methods :) , like the bpb,ebpb headers , FAT1,FAT2 .
        res = get_root_items(priv , disk );
        if (res != FLUSHOS_EGOOD){
            disk_stream_destroy(priv->data_stream);
            disk_stream_destroy(priv->root_stream);
            kfree(priv);
            return res;
        }



        // set the result pointer 
        (*priv_dptr) = priv;
        return FLUSHOS_EGOOD;
    }


#endif 