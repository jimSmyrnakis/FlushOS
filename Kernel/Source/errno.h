#ifndef __FLUSHOS_ERRNO_H__
#define __FLUSHOS_ERRNO_H__

    #include <stdint-gcc.h>
    #include <stddef.h>

    typedef int32_t errno;
    // error codes
    #define FLUSHOS_EGOOD       ((errno)0)
    #define FLUSHOS_EUNKNOWN    ((errno)0x80000000) // Unknown Error
    #define FLUSHOS_EBADARG     ((errno)1)          // Bad Arguments
    #define FLUSHOS_EBADPATH    ((errno)2)          // Bad path 
    #define FLUSHOS_ENOMEM      ((errno)3)          // No Memory
    #define FLUSHOS_ENIMPL      ((errno)4)          // Not Implemented
    #define FLUSHOS_EFSNOTUS    ((errno)5)          // 
    #define FLUSHOS_ENOBNDFS    ((errno)6)
    #define FLUSHOS_EINVLDISK   ((errno)7)          // Invalid Disk
    #define FLUSHOS_EINVLDFS    ((errno)8)          // Invalid File System
    #define FLUSHOS_EINVLDDESCR ((errno)9)          // Invalid Descriptor
    #define FLUSHOS_INVLDIO     ((errno)10)         // Invalid IO 
    // warning codes
    

#endif 