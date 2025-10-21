#ifndef __FAT16_RESOLVE_GET_ROOT_DIRS__
#define __FAT16_RESOLVE_GET_ROOT_DIRS__

    #include "inc.h"

    static errno init_fat16_private_root_directory(struct fat16_private* priv , struct disk* disk){
        // first we set that header of fat16 is loaded and everything else except root dirs
        
        // A root directory is nothing else that a unamed folder that is the beggining 
        // of our file system and is responsible for showing us the first files/directories
        // . Yes no magic at all just simple logic
        // Headers (bpb,ebpb) + Bootloader
        // Reseved Sectors
        // FAT1,
        // FAT2(optional)
        // Root dir (a list of items where the count is defined in the headers)
        // Data Clusters (dirs/drivers/files all here - Clusters 0,1 are for special puprose)
        // Yes the size of a cluster , how many reseved sectors , how many each sectors fat 
        // is taken , if FAT2 exist's (is just a backup) , how many items (root files/dirs/drivers)
        // are in root dir all of them are in the headers . Headers (bpb,ebpb) have signature and
        // expected values that they define fat16 format and some hardware info that may filled in from 
        // bios , still do not trust them , ask the hardware it self always not expect everything from
        // bios .  

        // take the first sector for our root directory
        uint32_t root_dir_first_sector = 
            priv->header.bios_parameter_block.reserved_sectors + 
            (priv->header.bios_parameter_block.fat_copies *
             priv->header.bios_parameter_block.sectors_per_fat);

        // short name for the number of items in the root (x:/ is always refers to the 
        // root folder so we must be carefull and always save the new items back )
        uint32_t root_dir_entries = priv->header.bios_parameter_block.root_dir_entries;

        // how many bytes the root dir has ?
        uint32_t root_dir_size = root_dir_entries * sizeof(struct fat16_directory_item);

        // now find the total number of sectors required for them
        uint32_t total_sectors = root_dir_size / disk->sector_size;
        if (root_dir_size % disk->sector_size){
            total_sectors ++;
        }

        // initiallize our streams to point in the right place

        errno res;

        // now data stream is after the last sector of the root dir
        res = disk_stream_seek(priv->data_stream , SEEK_SET , 
            (root_dir_first_sector + total_sectors) * disk->sector_size);
        if (res != FLUSHOS_EGOOD){
            return res;
        }

        //the root stream 
        res = disk_stream_seek(priv->root_stream , SEEK_SET , 
        root_dir_first_sector * disk->sector_size);
        if (res != FLUSHOS_EGOOD){
            return res;
        }

        // finally just caculate the first and last sector for our root directory
        priv->root_directory.first_sector = root_dir_first_sector;
        priv->root_directory.last_sector = root_dir_first_sector + total_sectors;
        
        // we define streams position in bytes , so be carefull caculate only sector number 
        // is wrong

        return FLUSHOS_EGOOD;
    }

#endif 