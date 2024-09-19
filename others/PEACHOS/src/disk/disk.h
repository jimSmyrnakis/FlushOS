#ifndef DISK_H
#define DISK_H

    #include <status.h>
    #include <config.h>
    #include <fs/file.h>


    
    typedef uint32_t PEACHOS_DISK_TYPE;
    #define PEACHOS_DISK_TYPE_REAL ((PEACHOS_DISK_TYPE)0)
    struct disk{
        PEACHOS_DISK_TYPE type;
        uint16_t sector_size;
        struct file_system* file_system;

    };

    void disk_search_and_init(void);

    struct disk* disk_get(uint16_t index);

    int disk_read_blocks(struct disk* idisk , uint32_t lba , uint8_t count , void* buffer);
    
#endif 