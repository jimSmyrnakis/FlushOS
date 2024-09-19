#include "pde.h"

#define P   (X86_32_SET_BIT(uint32_t , 0))
#define WR  (X86_32_SET_BIT(uint32_t , 1))
#define US  (X86_32_SET_BIT(uint32_t , 2))
#define PWT (X86_32_SET_BIT(uint32_t , 3))
#define PCD (X86_32_SET_BIT(uint32_t , 4))
#define A   (X86_32_SET_BIT(uint32_t , 5))

#define PHYSICAL_ADDRESS_MASK (0xFFFFF000) 

x86_32_err_type X86_32_CALL x86_32_pde_set(_x86_32_pde* dest , const struct x86_32_pde* src){
    x86_32_err_type err = X86_32_E_OK;

    //read physical address
    if (src->ptaddr % X86_32_32BIT_PAGING_TABLE_ALLIGN_VALUE){
        err = X86_32_E_BPTA;
        goto out;
    }

    //initiallize entry
    (*dest) = 0;

    //set present
    x86_32_fast_set(  src->p ,  dest , P   );
    //set writable
    x86_32_fast_set(  src->wr, dest  , WR  );
    //set user mode
    x86_32_fast_set(  src->us, dest  , US  );
    //set write through
    x86_32_fast_set(  src->pwt ,dest , PWT );
    //set cache disable
    x86_32_fast_set( src->pcd  , dest , PCD );
    //set access
    x86_32_fast_set(  src->a, dest   , A   );
    //set page frame physical address
    (*dest) |= (src->ptaddr & PHYSICAL_ADDRESS_MASK);


out:
    return err;
}

void X86_32_CALL x86_32_pde_get(struct x86_32_pde* dest , const _x86_32_pde* src){

    //get present
    x86_32_fast_get(  src  ,P  ,  dest->p  );
    //get writable
    x86_32_fast_get( src , WR  , dest->wr  );
    //get user mode
    x86_32_fast_get( src , US  , dest->us  );
    //get page write through cache
    x86_32_fast_get( src , PWT , dest->pwt );
    //get paging cache disable
    x86_32_fast_get( src , PCD , dest->pcd );
    //get access
    x86_32_fast_get( src , A   , dest->a   );
    //get page table physical address
    dest->ptaddr = ((*src) & PHYSICAL_ADDRESS_MASK );

}