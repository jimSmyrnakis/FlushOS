#ifndef __FLUSHOS_DEVICE_H__
#define __FLUSHOS_DEVICE_H__

    #include <stdint.h>
    #include <stddef.h>
    #include "../errno.h"

    typedef uint32_t dev_flags;
    enum {
        DEVICE_FLAG_READ_ONLY = 0x00000001
    };

    struct device_info{
        uint64_t version    ;    /* Version of the device that is supported */ 
        void*    data       ;    /* Private pointer to data that the device understands */
        uint32_t identifier ;    /* Identity of the driver */
    };

    struct device_operations{
        errno (*open)(struct device_info* info , void* data);
        errno (*close)(struct device_info* info );
    };

#endif 