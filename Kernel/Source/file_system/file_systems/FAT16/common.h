#ifndef __FAT16_COMMON_C__
#define __FAT16_COMMON_C__

    #include "fat16.h"
    #include <config.h>
    // all common functions are here , i find that very usefull 
    // for the future

    void release_private_data(struct fat16_private* priv);

    void fat16_free_directory(struct fat16_directory dir);

    void fat16_to_proper_string(char** out, const char* in);


    void fat16_get_full_relative_filename(struct fat16_directory_item* item, char* out, int max_len);

    

    uint32_t cluster_get_info(
        uint32_t cluster ,
        struct disk* disk ,
        uint32_t* cluster_sector ,
        uint32_t* cluster_bytes , 
        uint32_t* cluster_sectors);

    bool fat16_is_cluster_used(fat16_entry cluster);

    uint32_t fat16_get_cluster_from_directory_item(struct fat16_directory_item* item);

    void fat16_free_item(struct fat16_item* item);

    void* fat16_read_data_cluster(struct disk* disk , fat16_entry cluster , uint32_t count);



    struct fat16_item* fat16_load_item_from_disk( // this method supports only one cluster for moment
        struct disk* disk ,
        struct fat16_directory_item* item);

    errno get_root_items(struct fat16_private* priv , struct disk* disk);

    errno init_fat16_private_root_directory(struct fat16_private* priv , struct disk* disk);
    
    errno init_fat16_private(struct fat16_private** priv_dptr , struct disk* disk);
    
    bool is_fat16_header(struct fat16_header header);

    void fat16_free_fat16_descriptor(struct fat16_descriptor* desc);

    struct fat16_item* fat16_descriptor_get_item(struct disk* disk , struct path_part* part);

    struct fat16_item* fat16_find_item_in_directory(
        struct disk* disk, 
        struct fat16_directory* dir, 
        struct path_part* part
    );
#endif 