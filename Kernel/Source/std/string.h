#ifndef __FLUSHOS_STRING_H__
#define __FLUSHOS_STRING_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>

    size_t strlen(const char* str);
    size_t strnlen(const char* str , size_t max_len);
    int str_to_digit(char c);
    bool str_is_digit(char c);

#endif 