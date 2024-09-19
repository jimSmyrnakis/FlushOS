#ifndef ALGO_STRING_H
    #define ALGO_STRING_H
    
    #include <stdint.h>
    #include <stddef.h>

    typedef uint32_t size_t;
    typedef  int32_t ssize_t;
    typedef unsigned char ascii;

    size_t ascii_len(const ascii* str);

    size_t ascii_len_s(const ascii* str , size_t max_length);

    int ascii_cpy(ascii* dest , const ascii* src );

    int ascii_cpy_s(ascii* dest , const ascii* src , size_t dest_length , size_t src_length);

    int ascii_cmp(const ascii* str1 , const ascii* str2 );

    int ascii_cmp_s(const ascii* str1 , const ascii* str2 , size_t str1_length , size_t str2_length);

    int ascii_def(ascii* str , ascii default_value);

    int ascii_def_s(ascii* str , ascii default_value , size_t max_length);

#endif 