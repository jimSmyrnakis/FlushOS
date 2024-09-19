#include "ecode.h"

#define GPECODE_EXT         X86_32_SET_BIT(_x86_32_ecode ,  0)
#define GPECODE_IDT         X86_32_SET_BIT(_x86_32_ecode ,  1)
#define GPECODE_TI          X86_32_SET_BIT(_x86_32_ecode ,  2)
#define GPECODE_INDEX_MASK  ((_x86_32_ecode) 0xFFF8)
#define GPECODE_INDEX_BMOV  3

void X86_32_CALL x86_32_gpecode_get(struct x86_32_gpecode* dest , const _x86_32_ecode* src){

    x86_32_fast_get(src , GPECODE_EXT , dest->ext   );
    x86_32_fast_get(src , GPECODE_IDT , dest->idt   );
    x86_32_fast_get(src , GPECODE_TI  , dest->ti    );
    dest->index = ( ((*src) & GPECODE_INDEX_MASK) >> GPECODE_INDEX_BMOV );

}

void X86_32_CALL x86_32_gpecode_set(_x86_32_ecode* dest , const struct x86_32_gpecode* src){
    
    (*dest) = 0;
    x86_32_fast_set(src->ext    , dest , GPECODE_EXT   );
    x86_32_fast_set(src->idt    , dest , GPECODE_IDT   );
    x86_32_fast_set(src->ti     , dest , GPECODE_TI    );
    (*dest) |= (src->index << GPECODE_INDEX_BMOV);

}


#define PFECODE_P       X86_32_SET_BIT(_x86_32_ecode ,  0)
#define PFECODE_WR      X86_32_SET_BIT(_x86_32_ecode ,  1)
#define PFECODE_US      X86_32_SET_BIT(_x86_32_ecode ,  2)
#define PFECODE_RSVD    X86_32_SET_BIT(_x86_32_ecode ,  3)
#define PFECODE_ID      X86_32_SET_BIT(_x86_32_ecode ,  4)

void X86_32_CALL x86_32_pfecode_get(struct x86_32_pfecode* dest , const _x86_32_ecode* src){

    x86_32_fast_get(src , PFECODE_P    , dest->p    );
    x86_32_fast_get(src , PFECODE_WR   , dest->wr   );
    x86_32_fast_get(src , PFECODE_US   , dest->us   );
    x86_32_fast_get(src , PFECODE_RSVD , dest->rsvd );
    x86_32_fast_get(src , PFECODE_ID   , dest->id   );

}

void X86_32_CALL x86_32_pfecode_set(_x86_32_ecode* dest , const struct x86_32_pfecode* src){

    x86_32_fast_set( src->p    , dest , PFECODE_P    );
    x86_32_fast_set( src->wr   , dest , PFECODE_WR   );
    x86_32_fast_set( src->us   , dest , PFECODE_US   );
    x86_32_fast_set( src->rsvd , dest , PFECODE_RSVD );
    x86_32_fast_set( src->id   , dest , PFECODE_ID   );

}


