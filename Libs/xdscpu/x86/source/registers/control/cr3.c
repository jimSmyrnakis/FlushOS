#include "cr3.h"

#define PDB_ADDRESS ((uint32_t) 0xFFFFF000)
#define PWT (X86_32_SET_BIT( uint32_t , 3 ))
#define PCD (X86_32_SET_BIT( uint32_t , 4 ))

#define x86_32_cr3_set_fast( cond , dest , value) (*(dest)) = ( (cond) ? ( (*(dest)) | (value) ) : ( (*(dest)) & ~(value) ) )

x86_32_err_type X86_32_CALL x86_32_cr3_set(_x86_32_cr3* dest ,const struct x86_32_cr3* src){
    if ( (src->pdbase % 4096) != 0 )
        return X86_32_E_PAGE_DIR_NOT_ALLIGN;
    
    (*dest) = PDB_ADDRESS & src->pdbase;

    x86_32_fast_set( src->pwt , dest , PWT );
    x86_32_fast_set( src->pcd , dest , PCD );

    return X86_32_E_OK;
}

#define x86_32_cr3_get_fast( src , val , dest ) (dest) = ( ( (*(src)) & (val) ) ? true : false )

void X86_32_CALL x86_32_cr3_get(struct x86_32_cr3* dest ,const _x86_32_cr3* src){
    dest->pdbase = (*src) & PDB_ADDRESS ;

    x86_32_fast_get( src , PWT , dest->pwt );
    x86_32_fast_get( src , PCD , dest->pcd );
    
}


