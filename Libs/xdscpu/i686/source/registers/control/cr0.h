#ifndef X86_32_CR0_H
#define X86_32_CR0_H

    #include "../../core.h"
    #include "../../error.h"

    struct x86_32_cr0{
        
        bool pe; // protection mode enable                                          --bit 00
        bool mp; //                                                                 --bit 01
        bool em; //                                                                 --bit 02
        bool ts; //                                                                 --bit 03
        bool et; //                                                                 --bit 04
        bool ne; //                                                                 --bit 05
        //reserved
        bool wp; //enable paging protection                                         --bit 16
        //reserved
        bool am; //                                                                 --bit 18
        //reserved
        bool nw; //                                                                 --bit 29
        bool cd; //                                                                 --bit 30
        bool pg; // paging enable                                                   --bit 31
    };

    typedef uint32_t _x86_32_cr0;
    extern void X86_32_CALL _x86_32_cr0_write(const _x86_32_cr0* reg_value);
    extern void X86_32_CALL _x86_32_cr0_read (const _x86_32_cr0* reg_value);

    void X86_32_CALL x86_32_cr0_set(_x86_32_cr0* dest ,const struct x86_32_cr0* src);
    void X86_32_CALL x86_32_cr0_get(struct x86_32_cr0* dest ,const _x86_32_cr0* src);
    
#endif