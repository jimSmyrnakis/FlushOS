#ifndef __FLUSHOS_FAT16_READ_DATA_CLUSTERS_C__
#define __FLUSHOS_FAT16_READ_DATA_CLUSTERS_C__

    #include "fat16.h"
    #include "open/inc.h"

    

    void* fat16_read_data_cluster(struct disk* disk , fat16_entry cluster , uint32_t count){
        if ( (disk == NULL) || (cluster <= 1) || (count == 0))
            return NULL;

        

        struct fat16_private* priv = disk->priv;
        //FirstDataSector = ReservedSectorCount 
        //        + (NumFATs * FATSize)
        //        + RootDirSectors

        uint32_t cluster_first_sector ;
        uint32_t sectors_per_cluster;
        uint32_t bytes_total ;
        cluster_get_info(cluster , disk , &cluster_first_sector , &bytes_total , &sectors_per_cluster);
        uint8_t* data_cluster = kzalloc(count * bytes_total);
        if (data_cluster == NULL)   return NULL;

        // based on the fat table FAT1 load every cluster

        fat16_entry current_cluster = cluster ;
        fat16_entry next_cluster ;
        for (uint32_t i = 0;  i < count ; i++){
            // for each cluster 
            
            errno res = 
            disk_read_sector(
                disk  , cluster_first_sector , 
                sectors_per_cluster , data_cluster + bytes_total * i );
            if (res != FLUSHOS_EGOOD){
                kfree(data_cluster);
                return NULL;
            }
            current_cluster = priv->FAT1[cluster];
            if (fat16_is_cluster_used(current_cluster) == false){
                break;
            }
        }

        

        return data_cluster;
        
    }

    

#endif 