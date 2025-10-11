#ifndef __FLUSHOS_DISK_H__
#define __FLUSHOS_DISK_H__

    #include <stdint.h>
    #include <stddef.h>
    #include "../errno.h"
    // this is a abstraction layer for all our disk accesses :)
    // and even may change for all different platforms , this os
    // focuses in supporting many different platforms , like dektop to
    // rasbery  py etc. 
    enum disk_type{
        DISK_TYPE_PATA_PRIMARY 
    };
    typedef errno (*disk_read)(uint64_t lba, uint32_t total, void* buffer);

    struct disk{
        enum disk_type type;
        uint32_t  sector_size;
        disk_read read_function;
        
    };
    // every detail , everything that has to do with each disk (like the number of sectors)
    // the sector size in bytes , some names of the disk , its type and stuff will abstracted 
    // away from the implementation so in the future we can do some very cool stuff :))))

    void disk_init(void);
    struct disk* disk_get(int index);
    errno disk_read_sector( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer );
    
#endif 