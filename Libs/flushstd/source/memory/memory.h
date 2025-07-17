#ifndef ALGO_MEMORY_H
    #define ALGO_MEMORY_H

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>

    int memcpy(void* dest ,const void* src ,int cnt);

    int memcmp(void* dt1 , void* dt2 , int cnt , bool littleEndian);
    int memwrite( void* base , int cnt , uint8_t default_value , bool little_endian);

#endif