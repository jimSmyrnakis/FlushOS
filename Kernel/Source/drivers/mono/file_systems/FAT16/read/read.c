#include "common.c"

errno fat16_read(
    struct disk* disk, 
    void* private, 
    uint32_t size, 
    uint32_t nmemb, 
    char* out){

    
    //dsfasaf
    struct fat16_descriptor* descr = (struct fat16_descriptor*)private;

    uint32_t cluster_sectors = 0 , cluster_first_sector = 0, cluster_bytes = 0 ;
    uint32_t first_file_cluster = fat16_get_cluster_from_directory_item(&descr->item->file);
    // 
    cluster_get_info( first_file_cluster
    , disk , &cluster_first_sector , &cluster_bytes  , &cluster_sectors);

    // amount of clusters
    uint32_t clusters_amount = (size * nmemb ) / cluster_bytes;
    if ((size * nmemb ) % cluster_bytes) clusters_amount++;
    // so we need that many clusters at least;

    // Now witch one is the first one cluster we will need
    uint32_t clusters_offset = descr->pos / cluster_bytes;
    void* clusters_data = 
    fat16_read_data_cluster(disk , first_file_cluster + clusters_offset , clusters_amount);
    if (clusters_data == NULL)
        return FLUSHOS_ENOMEM;

    // now we have all clusters data we need the in cluster offset based on pos
    uint32_t in_cluster_offset = descr->pos % cluster_bytes;
    
    // copy the result in the output 
    memcpy(out ,  clusters_data + in_cluster_offset , size * nmemb);

    // This implementation is the simples't one (no caching clusters)
    // no write through or write back logic , slow and simple
    descr->pos += size * nmemb;
    return FLUSHOS_EGOOD;
} 