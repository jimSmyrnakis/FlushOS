#ifndef X86_32_CR4_H
#define X86_32_CR4_H

    #include "../../core.h"
    #include "../../error.h"

    struct x86_32_cr4{
        bool vme        ; //                                                --bit 00 
        bool pvi        ; //                                                --bit 01 
        bool tsd        ; //                                                --bit 02 
        bool de         ; //                                                --bit 03 
        bool pse        ; //                                                --bit 04 
        bool pae        ; //                                                --bit 05 
        bool mce        ; //                                                --bit 06 
        bool pge        ; //                                                --bit 07 
        bool pce        ; //                                                --bit 08 
        bool osfxsr     ; //                                                --bit 09 
        bool osxmmexcpt ; //                                                --bit 10 
        bool umip       ; //                                                --bit 11
        bool la57       ; //                                                --bit 12 
        bool vmxe       ; //                                                --bit 13 
        bool smxe       ; //                                                --bit 14 
        //reserved
        bool fsgsbase   ; //                                                --bit 16 
        bool pcide      ; //                                                --bit 17 
        bool osxsave    ; //                                                --bit 18 
        bool kl         ; //                                                --bit 19 
        bool smep       ; //                                                --bit 20 
        bool smap       ; //                                                --bit 21 
        bool pke        ; //                                                --bit 22 
        bool cet        ; //                                                --bit 23 
        bool pks        ; //                                                --bit 24 
        bool uintr      ; //                                                --bit 25 
    };

    typedef uint32_t _x86_32_cr4;

    extern void X86_32_CALL _x86_32_cr4_write(const _x86_32_cr4* reg_value);
    extern void X86_32_CALL _x86_32_cr4_read (const _x86_32_cr4* reg_value);

    void X86_32_CALL x86_32_cr4_set(_x86_32_cr4* dest ,const struct x86_32_cr4* src);
    void X86_32_CALL x86_32_cr4_get(struct x86_32_cr4* dest ,const _x86_32_cr4* src);

#endif 