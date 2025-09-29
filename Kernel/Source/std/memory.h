#ifndef __FLUSHOS_STD_MEMORY_H__
#define __FLUSHOS_STD_MEMORY_H__

    #include <stdint.h>
    #include <stddef.h>

    // a simple implementation of the memset
    void* memset(void* ptr , int c , size_t size);
    // TODO : make the memset using assembly for more perfomance
    // not very necessery but a intresting one

#endif 