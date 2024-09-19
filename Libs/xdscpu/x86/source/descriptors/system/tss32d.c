#include "tss32d.h"

#define TSS32D_TYPE_NBUSY ((uint32_t) 0x00000900)
#define TSS32D_TYPE_BUSY  ((uint32_t) 0x00000B00)
#define TYPE_GEN          ((uint32_t) 0x00001F00)
#define MINIMUM_TSS_LIMIT ((uint32_t) 0x00000068)

x86_32_err_type X86_32_CALL x86_32_descriptor_set_tss32d(struct x86_32_tss32d* dest , const struct _x86_32_descriptor* src){
    
    x86_32_err_type err = X86_32_E_OK;
    
    //check type and take busy flag too
    switch (src->dword2 & TYPE_GEN ){
        case TSS32D_TYPE_BUSY   : dest->busy = true ; break;
        case TSS32D_TYPE_NBUSY  : dest->busy = false; break;
        default                 : err = X86_32_E_INVALID_DESCRIPTOR_TYPE; goto out; 
    }

    //get base address
    x86_32_descriptor_get_base(src , &dest->baseaddr);

    //check and get limit
    x86_32_descriptor_get_limit(src , &dest->limit);
    if (dest->limit < MINIMUM_TSS_LIMIT){
        err = X86_32_E_TSS32LMTSML;
        goto out;
    }
    if (!x86_32_check_segment_size(dest->baseaddr , dest->limit)){
        err = X86_32_E_BSGMNTSPC;
        goto out;
    }
    
    //get present flag
    x86_32_descriptor_get_present(src , &dest->present);

    //get descriptor privilige level
    x86_32_descriptor_get_dpl(&dest->dpl , src);
    
out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_descriptor_get_tss32d(struct _x86_32_descriptor* dest , const struct x86_32_tss32d* src){

    x86_32_err_type err = X86_32_E_OK;
    
    //initiallize descriptor
    x86_32_descriptor_init(dest);

    //set descriptor type
    dest->dword2 |= ((src->busy) ? TSS32D_TYPE_BUSY : TSS32D_TYPE_NBUSY) ;

    //set descriptor base address
    x86_32_descriptor_set_base(dest , src->baseaddr , NULL);

    //check limit
    if (src->limit < MINIMUM_TSS_LIMIT){
        err = X86_32_E_TSS32LMTSML;
        goto out;
    }

    //set limit;
    err = x86_32_descriptor_set_limit(dest , src->limit , NULL);
    if (err != X86_32_E_OK)
        goto out;

    //set present
    x86_32_descriptor_set_present(dest , src->present);

    //set dpl
    x86_32_descriptor_set_dpl(dest , &src->dpl);

out:
    return err;
}
