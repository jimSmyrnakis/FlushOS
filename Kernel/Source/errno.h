#ifndef __FLUSHOS_ERRNO_H__
#define __FLUSHOS_ERRNO_H__

    #include <stdint.h>
    #include <stddef.h>

    typedef int32_t errno;
    // error codes
    #define FLUSHOS_EGOOD       ((errno)0)
    #define FLUSHOS_EUNKNOWN    ((errno)0x80000000)
    #define FLUSHOS_EBADARG     ((errno)1)
    #define FLUSHOS_EBADPATH    ((errno)2)
    #define FLUSHOS_ENOMEM      ((errno)3)
    #define FLUSHOS_ENIMPL      ((errno)4)
    #define FLUSHOS_EFSNOTUS    ((errno)5)
    // warning codes
    

#endif 