#include "string.h"

size_t strlen(const char* str){
    if (!str) return 0;

    size_t len = 0;
    while ( str[len] != '\0'){
        len++;
    }
    return len;
}

size_t strnlen(const char* str , size_t max_len){
    if (!str) return 0;

    size_t len = 0;
    while ( str[len] != '\0'){
        len++;
        if (len > max_len)
            return 0;
    }
    return len;
}



int str_to_digit(char c){
    return c - '0';
}

bool str_is_digit(char c){
    int digit = str_to_digit(c);
    return (digit >= 0 ) && (digit <= 9) ;
}

