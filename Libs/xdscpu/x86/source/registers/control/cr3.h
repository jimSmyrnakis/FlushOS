#ifndef X86_32_CR3_H
#define X86_32_CR3_h

    #include "../../core.h"
    #include "../../error.h"

    struct x86_32_cr3{
        uint32_t pdbase;       // 4KB allign physical address of the page directory        - (31-12)
        bool     pwt;                       // paging cache write through enable                        - (bit 3)
        bool     pcd;                       // paging cache disable                                     - (bit 4)
        // pwt and pcd is for access paging directory entries
    };

    typedef uint32_t _x86_32_cr3;

    extern void X86_32_CALL _x86_32_cr3_write(const _x86_32_cr3* reg_value);
    extern void X86_32_CALL _x86_32_cr3_read (const _x86_32_cr3* reg_value);

    x86_32_err_type X86_32_CALL x86_32_cr3_set(_x86_32_cr3* dest ,const struct x86_32_cr3* src);
    void            X86_32_CALL x86_32_cr3_get(struct x86_32_cr3* dest ,const _x86_32_cr3* src);

#endif 