#ifndef X86_32_PTE_H
#define X86_32_PTE_H

    #include "../core.h"
    #include "../error.h"

    #define X86_32_32BIT_PAGING_FRAME_ALLIGN_VALUE ((uint32_t)4096)

    typedef uint32_t _x86_32_pte;
    
    struct x86_32_pte{
        bool p ;    // present bit                  --bit 0
        bool wr;    // writable bit                 --bit 1
        bool us;    // user/supervisor bit          --bit 2
        bool pwt;   // paging cache write through   --bit 3
        bool pcd;   // paging caching disable       --bit 4
        bool a  ;   // access bit                   --bit 5
        bool d  ;   // dirty  bit                   --bit 6
        
        //bit 7 is reserved and
        //bits 8-11 are ignore or enable mechanism for intel processor's that may not exist

        uint32_t pfaddr;             //             --bit 12 - 31
    };

    x86_32_err_type X86_32_CALL x86_32_pte_set(_x86_32_pte* dest , const struct x86_32_pte* src);
    void            X86_32_CALL x86_32_pte_get(struct x86_32_pte* dest , const _x86_32_pte* src);
    

#endif