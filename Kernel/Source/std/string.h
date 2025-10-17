#ifndef __FLUSHOS_STRING_H__
#define __FLUSHOS_STRING_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>

    size_t strlen(const char* str);
    size_t strnlen(const char* str , size_t max_len);
    size_t strnlen_terminator(const char* str, size_t max, char terminator);
    int    strncmp(const char* str1, const char* str2, size_t n);
    char*  strncpy(char* dest , const char* src , size_t len);
    int   istrncmp(const char* s1, const char* s2, size_t n);

    int str_to_digit(char c);
    bool str_is_digit(char c);
    char tolower(char s1);

#endif 