#ifndef STRING_H
#define STRING_H

    #include <def.h>
    #include <status.h>
    #include <config.h>
    
    
    ksize_t strlen(const char* str);
    ksize_t strnlen(const char* str , ksize_t maxLen);
    int strcmp(const char* str , const char* sstr );
    int strncmp(const char* str , const char* sstr , ksize_t maxLen);
    void strcpy(char* dest , const char* src);
    void strncpy(char* dest , const char* src , ksize_t maxLen);
    

#endif 