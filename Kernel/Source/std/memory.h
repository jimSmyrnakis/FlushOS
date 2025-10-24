#ifndef __FLUSHOS_STD_MEMORY_H__
#define __FLUSHOS_STD_MEMORY_H__

    #include <stdint-gcc.h>
    #include <stddef.h>

    // a simple implementation of the memset
    void* memset(void* ptr , int c , size_t size);
    int memcmp(const void* ptr1 , const void* ptr2 , size_t size);
    void* memcpy(void* dest ,const void* src , size_t size);

#endif 