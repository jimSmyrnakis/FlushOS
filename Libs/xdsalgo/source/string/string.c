#include "string.h"

size_t ascii_len(const ascii* str){
    size_t i = 0 ;
    while (str[i] != '\0')
        i++;
    
    return i;
}

size_t ascii_len_s(const ascii* str , size_t max_length){
    size_t i = 0 ;
    while ( (str[i] != '\0') && (i < max_length) )
        i++;
    
    return i;
}

int ascii_cpy(ascii* dest , const ascii* src ){
    size_t i;
    
    while (src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    
    return 0;
}

int ascii_cpy_s(ascii* dest , const ascii* src , size_t dest_length , size_t src_length){
    size_t i;
    
    while ( (src[i] != '\0') && (i < dest_length) && (i < src_length) ){
        dest[i] = src[i];
        i++;
    }

    if (i < dest_length)
        dest[i] = '\0';
    
    return 0;
}

int ascii_cmp(const ascii* str1 , const ascii* str2 ){
    size_t i = 0;
    while(str1[i] && str2[i]){

        if (str1[i] > str2[i])
            return +1;
        
        if (str1[i] < str2[i])
            return -1;

        i++;
    }

    if (str1[i])
        return +1;
    
    if (str2[i])
        return -1;

    return 0;
}

int ascii_cmp_s(const ascii* str1 , const ascii* str2 , size_t str1_length , size_t str2_length){
    size_t i = 0;
    while(str1[i] && str2[i] && (i < str1_length) && (i < str2_length)){

        if (str1[i] > str2[i])
            return +1;
        
        if (str1[i] < str2[i])
            return -1;

        i++;
    }

    if ((i < str1_length) && str1[i])
        return +1;
    
    if ((i < str2_length) && str2[i])
        return -1;

    return 0;
}

int ascii_def(ascii* str , ascii default_value){
    size_t i = 0;
    while(str[i]){
        str[i] = default_value;
        i++;
    }

    return 0;
}

int ascii_def_s(ascii* str , ascii default_value , size_t max_length){
    if ( max_length == 0)
        return 1;
    size_t i = 0 ;
    while( ( i < max_length) && str[i]){
        str[i] = default_value;
        i++;
    }
    return 0;
}



