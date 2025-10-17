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

char* strncpy(char* dest , const char* src , size_t len){

    if (!dest || !src || !len){
        return NULL;
    }

    for(size_t i = 0;  i < len; i++){
        dest[i] = src[i];
        if (src[i] == '\0')
            break;
    }

    dest[len - 1] = '\0';

    return dest;
}

size_t strnlen_terminator(const char* str, size_t max, char terminator)
{
    size_t i = 0;
    for(i = 0; i < max; i++)
    {
        if (str[i] == '\0' || str[i] == terminator)
            break;
    }

    return i;
}

int strncmp(const char* str1, const char* str2, size_t n)
{
    unsigned char u1, u2;

    while(n-- > 0)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}

int istrncmp(const char* s1, const char* s2, size_t n)
{
    unsigned char u1, u2;
    while(n-- > 0)
    {
        u1 = (unsigned char)*s1++;
        u2 = (unsigned char)*s2++;
        if (u1 != u2 && tolower(u1) != tolower(u2))
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}










char tolower(char s1)
{
    if (s1 >= 65 && s1 <= 90)
    {
        s1 += 32;
    }

    return s1;
}



int str_to_digit(char c){
    return c - '0';
}

bool str_is_digit(char c){
    int digit = str_to_digit(c);
    return (digit >= 0 ) && (digit <= 9) ;
}

