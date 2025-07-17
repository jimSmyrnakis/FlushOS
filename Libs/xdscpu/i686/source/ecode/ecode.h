#ifndef X86_32_ECODE_H
#define X86_32_ECODE_H

    #include "../core.h"
    #include "../error.h"

    struct x86_32_gpecode{ // general ecode format
        bool                    ext;        // external event           --bit 00
        bool                    idt;        // idt selector             --bit 01
        bool                    ti ;        // gdt/ldt selector         --bit 02
        uint16_t                index : 13; // selector index only      --bit 03 - 15
    };



    struct x86_32_pfecode{ // page fault ecode format
        bool p      ;   // present fault                            --bit 00
        bool wr     ;   // write/read cause the fault               --bit 01
        bool us     ;   // user/supervisor cause the fault          --bit 02
        bool rsvd   ;   // reserved bit on pte/pde cause the fault  --bit 03
        bool id     ;   // caused by instruction/data access        --bit 04
    };


    typedef uint32_t _x86_32_ecode;

    void X86_32_CALL x86_32_gpecode_get(struct x86_32_gpecode* dest , const _x86_32_ecode* src);
    void X86_32_CALL x86_32_gpecode_set(_x86_32_ecode* dest , const struct x86_32_gpecode* src);

    void X86_32_CALL x86_32_pfecode_get(struct x86_32_pfecode* dest , const _x86_32_ecode* src);
    void X86_32_CALL x86_32_pfecode_set(_x86_32_ecode* dest , const struct x86_32_pfecode* src);

    extern void X86_32_CALL _x86_32_ecode_read ( _x86_32_ecode* val ); 
    extern void X86_32_CALL _x86_32_ecode_write( _x86_32_ecode* val );
    //these functions to work , it must only called inside the exception procedure and not inside other called function on this procedure

#endif 