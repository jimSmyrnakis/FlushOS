#include "memory.h"

void* memset(void* ptr , int c , size_t size){
    char* cptr = (char*)ptr;

    for (size_t i = 0; i < size; i++){
        cptr[i] = (char)c;
    }

    return cptr;
}

int memcmp(const void* ptr1 , const void* ptr2 , size_t size){
    const uint8_t* a = (const uint8_t*)ptr1;
    const uint8_t* b = (const uint8_t*)ptr2;

    for (size_t i = 0; i < size; i++){
        if (a[i] != b[i]){
            return (a[i] > b[i]) ? 1 : -1;
        }
    }

    return 0;
}

void* memcpy(void* dest ,const void* src , size_t size){
    if (!dest || !src || !size)
        return NULL;

    uint8_t* destu8 = (uint8_t*)dest;
    const uint8_t* srcu8 = (const uint8_t*)src;
    for(size_t i = 0; i < size ; i++)
        destu8[i] = srcu8[i];
        
    return dest;
}