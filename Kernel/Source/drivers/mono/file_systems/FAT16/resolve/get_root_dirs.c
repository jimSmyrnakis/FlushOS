#ifndef __FAT16_RESOLVE_GET_ROOT_DIRS__
#define __FAT16_RESOLVE_GET_ROOT_DIRS__

    #include "inc.h"

    static errno init_fat16_private_root_directory(struct fat16_private* priv , struct disk* disk){
        // first we set that header of fat16 is loaded and everything else except root dirs
        
        uint32_t root_dir_first_sector = 
            priv->header.bios_parameter_block.reserved_sectors + 
            (priv->header.bios_parameter_block.fat_copies *
             priv->header.bios_parameter_block.sectors_per_fat);

        uint32_t root_dir_entries = priv->header.bios_parameter_block.root_dir_entries;
        uint32_t root_dir_size = root_dir_entries * sizeof(struct fat16_directory_item);
        uint32_t total_sectors = root_dir_size / disk->sector_size;
        if (root_dir_size % disk->sector_size){
            total_sectors ++;
        }
        priv->FAT_stream->pos = 
        priv->header.bios_parameter_block.reserved_sectors * disk->sector_size;

        priv->data_stream->pos = 0; 

        return FLUSHOS_EGOOD;
    }

#endif 