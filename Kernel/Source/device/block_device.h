#ifndef __FLUSHOS_BLOCK_DEVICE_H__
#define __FLUSHOS_BLOCK_DEVICE_H__

    #include <stdint.h>
    #include <stddef.h>
    #include "driver.h"
    #include "../errno.h"
    #include "common.h"

    struct block_device_operations{
        errno (*read_blocks) (struct driver_info* info , uint64_t lba , uint64_t count , void* buffer ); /*read blocks from the block device */
        errno (*write_blocks)(struct driver_info* info , uint64_t lba , uint64_t count , void* buffer ); /*write blocks to the block device */
    };


    

    struct block_device_attributes{
        uint64_t blkscnt; /*total blocks*/
        dev_flags flags ; /* flags of the device */

    };

    struct block_device{
        struct block_device_operations  oprs; /*operations for the block device */
        struct block_device_attributes  attr; /*attributes of the device */
    };

#endif 