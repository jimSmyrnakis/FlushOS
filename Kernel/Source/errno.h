#ifndef __FLUSHOS_ERRNO_H__
#define __FLUSHOS_ERRNO_H__

    #include <stdint.h>
    #include <stddef.h>

    typedef int32_t errno;
    // error codes
    #define FLUSHOS_EGOOD ((errno)-0)
    #define FLUSHOS_EUNKNOWN ((errno)0x80000000)

    // warning codes
    

#endif 