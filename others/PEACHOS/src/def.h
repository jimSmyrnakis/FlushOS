#ifndef DEF_H
#define DEF_H

    #include <stdint.h> 
    #include <stddef.h>

    typedef uint8_t  kbool;
    typedef uint32_t ksize_t;
    #define kfalse ((kbool)0)
    #define ktrue  ((kbool)1)
    #define isFlag(value , flag) (((value) & (flag)) == flag)
    #define KNULL ((void*)(0))
    #define LOGICAL_XOR(log1 , log2)((log1) && (!(log2))) || ((!(log1)) && (log2))

    #define  B  *((uint64_t)1)
    #define KB  *((uint64_t)1024  B)
    #define MB  *((uint64_t)1024 KB)
    #define GB  *((uint64_t)1024 MB)
    #define TB  *((uint64_t)1024 GB)

#endif 