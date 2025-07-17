#include "eflags.h"

#define EFLAGS_MUST_VAL ((_x86_32_eflags) 0x00000002 )
#define CF              X86_32_SET_BIT( _x86_32_eflags , 0)
#define PF              X86_32_SET_BIT( _x86_32_eflags , 2)
#define AF              X86_32_SET_BIT( _x86_32_eflags , 4)
#define ZF              X86_32_SET_BIT( _x86_32_eflags , 6)
#define SF              X86_32_SET_BIT( _x86_32_eflags , 7)
#define TF              X86_32_SET_BIT( _x86_32_eflags , 8)
#define IFX             X86_32_SET_BIT( _x86_32_eflags , 9)
#define DF              X86_32_SET_BIT( _x86_32_eflags , 10)
#define OF              X86_32_SET_BIT( _x86_32_eflags , 11)
#define NT              X86_32_SET_BIT( _x86_32_eflags , 14)
#define IOPL            ((_x86_32_eflags) 0x00003000)
#define IOPL_0          ((_x86_32_eflags) 0x00000000)
#define IOPL_1          ((_x86_32_eflags) 0x00001000)
#define IOPL_2          ((_x86_32_eflags) 0x00002000)
#define IOPL_3          ((_x86_32_eflags) 0x00003000)
#define RF              X86_32_SET_BIT( _x86_32_eflags , 16)
#define VM              X86_32_SET_BIT( _x86_32_eflags , 17)
#define AC              X86_32_SET_BIT( _x86_32_eflags , 18)
#define VIF             X86_32_SET_BIT( _x86_32_eflags , 19)
#define VIP             X86_32_SET_BIT( _x86_32_eflags , 20)
#define ID              X86_32_SET_BIT( _x86_32_eflags , 21)

void X86_32_CALL x86_32_eflags_set(_x86_32_eflags* dest ,const struct x86_32_eflags* src){

    x86_32_fast_set( src->cf  , dest , CF  );
    x86_32_fast_set( src->pf  , dest , PF  );
    x86_32_fast_set( src->af  , dest , AF  );
    x86_32_fast_set( src->zf  , dest , ZF  );
    x86_32_fast_set( src->sf  , dest , SF  );
    x86_32_fast_set( src->tf  , dest , TF  );
    x86_32_fast_set( src->IF  , dest , IFX );
    x86_32_fast_set( src->df  , dest , DF  );
    x86_32_fast_set( src->of  , dest , OF  );
    x86_32_fast_set( src->nt  , dest , NT  );
    x86_32_fast_set( src->rf  , dest , RF  );
    x86_32_fast_set( src->vm  , dest , VM  );
    x86_32_fast_set( src->ac  , dest , AC  );
    x86_32_fast_set( src->vif , dest , VIF );
    x86_32_fast_set( src->vip , dest , VIP );
    x86_32_fast_set( src->id  , dest , ID  );

    switch (src->iopl){
        case x86_32_pl_0: (*dest) |= IOPL_0; break;
        case x86_32_pl_1: (*dest) |= IOPL_1; break;
        case x86_32_pl_2: (*dest) |= IOPL_2; break;
        case x86_32_pl_3: (*dest) |= IOPL_3; break;
    }

}

void X86_32_CALL x86_32_eflags_get(struct x86_32_eflags* dest ,const _x86_32_eflags* src){

    x86_32_fast_get( src , CF  , dest->cf  );
    x86_32_fast_get( src , PF  , dest->pf  );
    x86_32_fast_get( src , AF  , dest->af  );
    x86_32_fast_get( src , ZF  , dest->zf  );
    x86_32_fast_get( src , SF  , dest->sf  );
    x86_32_fast_get( src , TF  , dest->tf  );
    x86_32_fast_get( src , IFX , dest->IF  );
    x86_32_fast_get( src , DF  , dest->df  );
    x86_32_fast_get( src , OF  , dest->of  );
    x86_32_fast_get( src , NT  , dest->nt  );
    x86_32_fast_get( src , RF  , dest->rf  );
    x86_32_fast_get( src , VM  , dest->vm  );
    x86_32_fast_get( src , AC  , dest->ac  );
    x86_32_fast_get( src , VIF , dest->vif );
    x86_32_fast_get( src , VIP , dest->vip );
    x86_32_fast_get( src , ID  , dest->id  );

    switch ((*src) & IOPL){
        case IOPL_0: dest->iopl = x86_32_pl_0; break;
        case IOPL_1: dest->iopl = x86_32_pl_1; break;
        case IOPL_2: dest->iopl = x86_32_pl_2; break;
        case IOPL_3: dest->iopl = x86_32_pl_3; break;
    }

}
