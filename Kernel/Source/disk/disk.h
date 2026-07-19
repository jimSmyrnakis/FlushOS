#ifndef __FLUSHOS_DISK_H__
#define __FLUSHOS_DISK_H__

    

    #include <stdint-gcc.h>
    #include <stddef.h>
    
    #include "../errno.h"
    

    struct disk_attributes{
        uint32_t sector_length;
        uint32_t zero;
        uint64_t sector_count;
        uint64_t lba_base;
        
    }__attribute__((packed));
    typedef struct disk_attributes disk_attributes;

    typedef errno (*disk_read_proc)(uint64_t lba, uint32_t total, void* buffer , void* priv);
    
    typedef errno (*disk_write_proc)(uint64_t lba , uint32_t total, void* buffer , void* priv);
    
    
    struct file_system;

    

    struct disk_module{
        disk_read_proc          read;
        disk_write_proc         write;
    }__attribute__((packed));

    typedef struct disk_module disk_module;

    struct disk{
        struct disk_attributes  attrs;
        struct disk_module      module;
        struct file_system*     fs;
        uint32_t                id;
        void*                   priv; 
    };
    typedef struct disk disk;

    void disk_init(void);

    errno disk_create(
        struct disk_module* module , 
        void* priv , struct disk_attributes attrs);
    
    struct disk* disk_get(int index);

    errno disk_destroy(struct disk* idisk);

    errno disk_read( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer );
    
    errno disk_write( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer);



    
    uint32_t disk_get_id(struct disk* idisk);

    uint16_t disk_get_max_disks(void);
    
    uint16_t disk_get_disks_count(void);
    

    
#endif 