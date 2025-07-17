#ifndef X86_32_PDE_H
#define X86_32_PDE_H

    #include "../core.h"
    #include "../error.h"

    #define X86_32_32BIT_PAGING_TABLE_ALLIGN_VALUE ((uint32_t) 4096)

    typedef uint32_t _x86_32_pde;
    
    struct x86_32_pde{
        bool p ;    // present bit                  --bit 0
        bool wr;    // writable bit                 --bit 1
        bool us;    // user/supervisor bit          --bit 2
        bool pwt;   // paging cache write through   --bit 3
        bool pcd;   // page   caching disable       --bit 4
        bool a  ;   // access bit                   --bit 5
        //bit 7 must be 0 otherwise if a 4MByte paging mechanism must be supported (31-22 bit of linear address are used for only the page dir
        //and page dir defines page frames of 4 MByte each ) . If this mechanism is not supperted the the bit is reserved and a reserved bit
        //will generate a page fault exception or a general porpuse exception 
        //bits 6 , 8-11 are ignore
        uint32_t ptaddr;            //           --bit 12 - 31
        //page table must have a allign 4KB address in physical memory otherwise the cpu will read undefined data 
    };

    x86_32_err_type X86_32_CALL x86_32_pde_set(_x86_32_pde* dest , const struct x86_32_pde* src);
    void            X86_32_CALL x86_32_pde_get(struct x86_32_pde* dest , const _x86_32_pde* src);


#endif