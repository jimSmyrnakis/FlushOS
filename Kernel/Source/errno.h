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
    #define FLUSHOS_EIO         ((errno)10)         // IO Error  
    #define FLUSHOS_ENODEV      ((errno)11)         // Not Detected (like driver didn't detect device) 
    #define FLUSHOS_EBADDISK    ((errno)12)         // Disk struct is bad , no callbacks or wrong other fields
    #define FLUSHOS_BADSTRCT    ((errno)13)         // kernel and given structs address are mismaching pointers
    #define FLUSHOS_EOOB        ((errno)14)         // Out Of Bounds 
    #define FLUSHOS_EINVLD      ((errno)15)
    #define FLUSHOS_EDNRDY      ((errno)16)         // disk not ready
    #define FLUSHOS_ETIMEOUT    ((errno)17)         // Time out 
    #define FLUSHOS_EREAD       ((errno)18)         // Read Error
    #define FLUSHOS_EWRITE      ((errno)19)         // error write
    #define FLUSHOS_EDTCRPT     ((errno)20)         // Error data corrupted
    #define FLUSHOS_EBBLCK      ((errno)21)         // error bad block
    #define FLUSHOS_EHWFAIL     ((errno)22)         // eror hardware failure
    #define FLUSHOS_ERMVD       ((errno)23)         // error removed
    #define FLUSHOS_EUNPRT      ((errno)24)         // error unsupported

    // warning codes
    

#endif 