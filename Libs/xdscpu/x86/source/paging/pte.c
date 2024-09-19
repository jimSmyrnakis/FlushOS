#include "pte.h"

#define P   (X86_32_SET_BIT(uint32_t , 0))
#define WR  (X86_32_SET_BIT(uint32_t , 1))
#define US  (X86_32_SET_BIT(uint32_t , 2))
#define PWT (X86_32_SET_BIT(uint32_t , 3))
#define PCD (X86_32_SET_BIT(uint32_t , 4))
#define A   (X86_32_SET_BIT(uint32_t , 5))
#define D   (X86_32_SET_BIT(uint32_t , 6))

#define PHYSICAL_ADDRESS_MASK (0xFFFFF000) 

#define x86_32_fast_set1( dest , cond , flag ) x86_32_fast_set(cond ,  dest, flag )

x86_32_err_type X86_32_CALL x86_32_pte_set(_x86_32_pte* dest , const struct x86_32_pte* src){
    x86_32_err_type err = X86_32_E_OK;

    //check physical address
    if (src->pfaddr % X86_32_32BIT_PAGING_FRAME_ALLIGN_VALUE){
        err = X86_32_E_BPFA;
        goto out;
    }

    //initiallize entry
    (*dest) = 0;

    //set present
    x86_32_fast_set1( dest , src->p   , P   );
    //set writable
    x86_32_fast_set1( dest , src->wr  , WR  );
    //set user mode
    x86_32_fast_set1( dest , src->us  , US  );
    //set write through
    x86_32_fast_set1( dest , src->pwt , PWT );
    //set cache disable
    x86_32_fast_set1( dest , src->pcd , PCD );
    //set access
    x86_32_fast_set1( dest , src->a   , A   );
    //set dirty
    x86_32_fast_set1( dest , src->d   , D   );
    //set page frame physical address
    (*dest) |= (src->pfaddr & PHYSICAL_ADDRESS_MASK);

out:
    return err;
}

#define x86_32_fast_get1(dest , src , flag) x86_32_fast_get(src , flag , dest)

void X86_32_CALL x86_32_pte_get(struct x86_32_pte* dest , const _x86_32_pte* src){

    //get present
    x86_32_fast_get1( dest->p   , src , P   );
    //get writable
    x86_32_fast_get1( dest->wr  , src , WR  );
    //get user mode
    x86_32_fast_get1( dest->us  , src , US  );
    //get page write through cache
    x86_32_fast_get1( dest->pwt , src , PWT );
    //get paging cache disable
    x86_32_fast_get1( dest->pcd , src , PCD );
    //get access
    x86_32_fast_get1( dest->a   , src , A   );
    //get dirty
    x86_32_fast_get1( dest->d   , src , D   );
    //get page frame physical address
    dest->pfaddr = ((*src) & PHYSICAL_ADDRESS_MASK );

}
