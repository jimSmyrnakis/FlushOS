#include "cr4.h"

#define VME        (X86_32_SET_BIT(uint32_t ,  0))
#define PVI        (X86_32_SET_BIT(uint32_t ,  1))
#define TSD        (X86_32_SET_BIT(uint32_t ,  2))
#define DE         (X86_32_SET_BIT(uint32_t ,  3))
#define PSE        (X86_32_SET_BIT(uint32_t ,  4))
#define PAE        (X86_32_SET_BIT(uint32_t ,  5))
#define MCE        (X86_32_SET_BIT(uint32_t ,  6))
#define PGE        (X86_32_SET_BIT(uint32_t ,  7))
#define PCE        (X86_32_SET_BIT(uint32_t ,  8))
#define OSFXSR     (X86_32_SET_BIT(uint32_t ,  9))
#define OSXMMEXCPT (X86_32_SET_BIT(uint32_t , 10))
#define UMIP       (X86_32_SET_BIT(uint32_t , 11))
#define LA57       (X86_32_SET_BIT(uint32_t , 12))
#define VMXE       (X86_32_SET_BIT(uint32_t , 13))
#define SMXE       (X86_32_SET_BIT(uint32_t , 14))
#define FSGSBASE   (X86_32_SET_BIT(uint32_t , 16))
#define PCIDE      (X86_32_SET_BIT(uint32_t , 17))
#define OSXSAVE    (X86_32_SET_BIT(uint32_t , 18))
#define KL         (X86_32_SET_BIT(uint32_t , 19))
#define SMEP       (X86_32_SET_BIT(uint32_t , 20))
#define SMAP       (X86_32_SET_BIT(uint32_t , 21))
#define PKE        (X86_32_SET_BIT(uint32_t , 22))
#define CET        (X86_32_SET_BIT(uint32_t , 23))
#define PKS        (X86_32_SET_BIT(uint32_t , 24))
#define UINTR      (X86_32_SET_BIT(uint32_t , 25))

#define x86_32_cr4_set_fast( cond , dest , value) (*(dest)) = ( (cond) ? ( (*(dest)) | (value) ) : ( (*(dest)) & ~(value) ) )

void X86_32_CALL x86_32_cr4_set(_x86_32_cr4* dest ,const struct x86_32_cr4* src){
    (*dest) = 0;

    x86_32_cr4_set_fast( src->vme        , dest , VME        );
    x86_32_cr4_set_fast( src->pvi        , dest , PVI        );
    x86_32_cr4_set_fast( src->tsd        , dest , TSD        );
    x86_32_cr4_set_fast( src->de         , dest , DE         );
    x86_32_cr4_set_fast( src->pse        , dest , PSE        );
    x86_32_cr4_set_fast( src->pae        , dest , PAE        );
    x86_32_cr4_set_fast( src->mce        , dest , MCE        );
    x86_32_cr4_set_fast( src->pge        , dest , PGE        );
    x86_32_cr4_set_fast( src->pce        , dest , PCE        );
    x86_32_cr4_set_fast( src->osfxsr     , dest , OSFXSR     );
    x86_32_cr4_set_fast( src->osxmmexcpt , dest , OSXMMEXCPT );
    x86_32_cr4_set_fast( src->umip       , dest , UMIP       );
    x86_32_cr4_set_fast( src->la57       , dest , LA57       );
    x86_32_cr4_set_fast( src->vmxe       , dest , VMXE       );
    x86_32_cr4_set_fast( src->smxe       , dest , SMXE       );

    x86_32_cr4_set_fast( src->fsgsbase   , dest , FSGSBASE   );
    x86_32_cr4_set_fast( src->pcide      , dest , PCIDE      );
    x86_32_cr4_set_fast( src->osxsave    , dest , OSXSAVE    );
    x86_32_cr4_set_fast( src->kl         , dest , KL         );
    x86_32_cr4_set_fast( src->smep       , dest , SMEP       );
    x86_32_cr4_set_fast( src->smap       , dest , SMAP       );
    x86_32_cr4_set_fast( src->pke        , dest , PKE        );
    x86_32_cr4_set_fast( src->cet        , dest , CET        );
    x86_32_cr4_set_fast( src->pks        , dest , PKS        );
    x86_32_cr4_set_fast( src->uintr      , dest , UINTR      );

}

#define x86_32_cr4_get_fast( src , val , dest ) (dest) = ( ( (*(src)) & (val) ) ? true : false )

void X86_32_CALL x86_32_cr4_get(struct x86_32_cr4* dest ,const _x86_32_cr4* src){

    x86_32_cr4_get_fast( src , VME        , dest->vme        );
    x86_32_cr4_get_fast( src , PVI        , dest->pvi        );
    x86_32_cr4_get_fast( src , TSD        , dest->tsd        );
    x86_32_cr4_get_fast( src , DE         , dest->de         );
    x86_32_cr4_get_fast( src , PSE        , dest->pse        );
    x86_32_cr4_get_fast( src , PAE        , dest->pae        );
    x86_32_cr4_get_fast( src , MCE        , dest->mce        );
    x86_32_cr4_get_fast( src , PGE        , dest->pge        );
    x86_32_cr4_get_fast( src , PCE        , dest->pce        );
    x86_32_cr4_get_fast( src , OSFXSR     , dest->osfxsr     );
    x86_32_cr4_get_fast( src , OSXMMEXCPT , dest->osxmmexcpt );
    x86_32_cr4_get_fast( src , UMIP       , dest->umip       );
    x86_32_cr4_get_fast( src , LA57       , dest->la57       );
    x86_32_cr4_get_fast( src , VMXE       , dest->vmxe       );
    x86_32_cr4_get_fast( src , SMXE       , dest->smxe       );

    x86_32_cr4_get_fast( src , FSGSBASE   , dest->fsgsbase   );
    x86_32_cr4_get_fast( src , PCIDE      , dest->pcide      );
    x86_32_cr4_get_fast( src , OSXSAVE    , dest->osxsave    );
    x86_32_cr4_get_fast( src , KL         , dest->kl         );
    x86_32_cr4_get_fast( src , SMEP       , dest->smep       );
    x86_32_cr4_get_fast( src , SMAP       , dest->smap       );
    x86_32_cr4_get_fast( src , PKE        , dest->pke        );
    x86_32_cr4_get_fast( src , CET        , dest->cet        );
    x86_32_cr4_get_fast( src , PKS        , dest->pks        );
    x86_32_cr4_get_fast( src , UINTR      , dest->uintr      );


}

