#include "cr0.h"

#define PE (X86_32_SET_BIT(uint32_t ,  0))
#define MP (X86_32_SET_BIT(uint32_t ,  1))
#define EM (X86_32_SET_BIT(uint32_t ,  2))
#define TS (X86_32_SET_BIT(uint32_t ,  3))
#define ET (X86_32_SET_BIT(uint32_t ,  4))
#define NE (X86_32_SET_BIT(uint32_t ,  5))
#define WP (X86_32_SET_BIT(uint32_t , 16))
#define AM (X86_32_SET_BIT(uint32_t , 18))
#define NW (X86_32_SET_BIT(uint32_t , 29))
#define CD (X86_32_SET_BIT(uint32_t , 30))
#define PG (X86_32_SET_BIT(uint32_t , 31))

void X86_32_CALL x86_32_cr0_set(_x86_32_cr0* dest ,const struct x86_32_cr0* src){
    (*dest) = 0;

    x86_32_fast_set( src->pe , dest , PE );
    x86_32_fast_set( src->mp , dest , MP );
    x86_32_fast_set( src->em , dest , EM );
    x86_32_fast_set( src->ts , dest , TS );
    x86_32_fast_set( src->et , dest , ET );
    x86_32_fast_set( src->ne , dest , NE );
    x86_32_fast_set( src->wp , dest , WP );
    x86_32_fast_set( src->am , dest , AM );
    x86_32_fast_set( src->nw , dest , NW );
    x86_32_fast_set( src->cd , dest , CD );
    x86_32_fast_set( src->pg , dest , PG );
}

void X86_32_CALL x86_32_cr0_get(struct x86_32_cr0* dest ,const _x86_32_cr0* src){

    x86_32_fast_get( src , PE , dest->pe );
    x86_32_fast_get( src , MP , dest->mp );
    x86_32_fast_get( src , EM , dest->em );
    x86_32_fast_get( src , TS , dest->ts );
    x86_32_fast_get( src , ET , dest->et );
    x86_32_fast_get( src , NE , dest->ne );
    x86_32_fast_get( src , WP , dest->wp );
    x86_32_fast_get( src , AM , dest->am );
    x86_32_fast_get( src , NW , dest->nw );
    x86_32_fast_get( src , CD , dest->cd );
    x86_32_fast_get( src , PG , dest->pg );

}



