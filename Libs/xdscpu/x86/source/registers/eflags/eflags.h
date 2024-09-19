#ifndef X86_32_EFLAGS_H
#define X86_32_EFLAGS_H

    #include "../../core.h"
    #include "../../error.h"

    typedef uint32_t _x86_32_eflags;

    struct x86_32_eflags{
        bool             cf;    // carry flag               --bit 00
        // one                                              --bit 01 reserved
        bool             pf;    // parity flag              --bit 02
        // zero                                             --bit 03 reserved
        bool             af;    // a?     flag              --bit 04
        // zero                                             --bit 05 reserved
        bool             zf;    // zero flag                --bit 06
        bool             sf;    // sign flag                --bit 07
        bool             tf;    // trap flag                --bit 08
        bool             IF;    // interrupt flag           --bit 09
        bool             df;    // direction flag           --bit 10
        bool             of;    // overflow flag            --bit 11
        enum x86_32_pl iopl;    // io privilige level       --bit 12-13
        bool             nt;    // nested task              --bit 14 
        // zero                                             --bit 15 reserved
        bool             rf;    // resume flag              --bit 16
        bool             vm;    // virtual 8086 mode flag   --bit 17
        bool             ac;    // alligment check          --bit 18
        bool            vif;    // virtual if               --bit 19
        bool            vip;    // virtual int. panding     --bit 20
        bool             id;    // idendification           --bit 21
        // zero                                             --bit 22-31 reserved
    };

    void X86_32_CALL x86_32_eflags_set(_x86_32_eflags* dest ,const struct x86_32_eflags* src);
    void X86_32_CALL x86_32_eflags_get(struct x86_32_eflags* dest ,const _x86_32_eflags* src);

    extern void X86_32_CALL _x86_32_eflags_write(const _x86_32_eflags* src );
    extern void X86_32_CALL _x86_32_eflags_read (      _x86_32_eflags* dest);




#endif 