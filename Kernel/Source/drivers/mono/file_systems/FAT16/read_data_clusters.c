#ifndef __FLUSHOS_FAT16_READ_DATA_CLUSTERS_C__
#define __FLUSHOS_FAT16_READ_DATA_CLUSTERS_C__

    #include "fat16.h"
    #include "open/inc.h"

    void* fat16_read_data_cluster(struct disk* disk , uint32_t cluster){
        if ( (disk == NULL) || (cluster <= 1) )
            return NULL;

        

        struct fat16_private* priv = disk->priv;
        //FirstDataSector = ReservedSectorCount 
        //        + (NumFATs * FATSize)
        //        + RootDirSectors

        // find first sector of the first data cluster
        uint32_t first_data_sector = priv->header.bios_parameter_block.reserved_sectors;
        first_data_sector += 
            priv->header.bios_parameter_block.fat_copies *
            priv->header.bios_parameter_block.sectors_per_fat;

        uint32_t root_sectors = (priv->header.bios_parameter_block.root_dir_entries 
            * sizeof(struct fat16_directory_item) );
        first_data_sector += 
             root_sectors / disk->sector_size;
        if (root_sectors % disk->sector_size){
            first_data_sector++;
        }
        uint32_t sector_per_cluster = priv->header.bios_parameter_block.sectors_per_cluster;
        uint32_t cluster_first_sector = first_data_sector + (cluster - 2) * sector_per_cluster ;

        uint32_t bytes_total = sector_per_cluster * disk->sector_size;
        uint8_t* data_cluster = kzalloc(bytes_total);
        if (data_cluster == NULL)   return NULL;

        errno res = disk_read_sector(disk  , cluster_first_sector , sector_per_cluster , data_cluster );
        if (res != FLUSHOS_EGOOD){
            kfree(data_cluster);
            return NULL;
        }


        return data_cluster;
        
    }
#endif 