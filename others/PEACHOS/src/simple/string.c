#include "string.h"

ksize_t strlen(const char* str){
    ksize_t sz = 0;
    while(str[sz] != '\0') sz++;

    return sz;
}

ksize_t strnlen(const char* str , ksize_t maxLen){
    ksize_t sz = 0;

    while ((str[sz] != '\0') && (sz < maxLen)) sz++;

    return sz;
}

int strcmp(const char* str , const char* sstr ){
    
    ksize_t i = 0;
    while((str[i] != '\0') && (sstr[i] != '\0')){
        if (str[i] > sstr[i])
            return 1;
        if (str[i] < sstr[i])
            return -1;
        i++;
    }

    if (str[i] > sstr[i])
        return 1;
    if (str[i] < sstr[i])
        return -1;
    
    return 0;
}

int strncmp(const char* str , const char* sstr , ksize_t maxLen){
    ksize_t i = 0;
    while((str[i] != '\0') && (sstr[i] != '\0') && (i < maxLen)){
        if (str[i] > sstr[i])
            return 1;
        if (str[i] < sstr[i])
            return -1;
        i++;
    }
    
    return 0;
}

void strcpy(char* dest , const char* src){
    ksize_t i = 0;
    while (src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    if (dest[i] != '\0')
        dest[i] =  '\0';
}
void strncpy(char* dest , const char* src , ksize_t maxLen){
    ksize_t i = 0;
    while ((src[i] != '\0') && (i < maxLen)){
        dest[i] = src[i];
        i++;
    }
    if (dest[i] != '\0')
        dest[i] =  '\0';
}



    