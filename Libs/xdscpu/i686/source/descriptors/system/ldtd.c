#include "ldtd.h"

#define LDT_DESCRIPTOR_TYPE X86_32_SET_BIT(uint32_t , 9)

x86_32_err_type X86_32_CALL x86_32_ldt_descriptor_set(struct x86_32_ldt_descriptor* dest , const struct _x86_32_descriptor* src){
    //check system descriptor type
    if ((src->dword2 & LDT_DESCRIPTOR_TYPE) != LDT_DESCRIPTOR_TYPE )
        return X86_32_E_INVALID_DESCRIPTOR_TYPE;
    
    //get base
    x86_32_descriptor_get_base(src , &dest->base);

    //get limit
    x86_32_descriptor_get_limit(src , &dest->limit);

    //get dpl
    x86_32_descriptor_get_dpl(&dest->dpl , src);

    //get present
    x86_32_descriptor_get_present(src , &dest->present);

    return X86_32_E_OK;
}

x86_32_err_type X86_32_CALL x86_32_ldt_descriptor_get(struct _x86_32_descriptor* dest , const struct x86_32_ldt_descriptor* src){
    x86_32_err_type err= X86_32_E_OK;
    //initiallize system descriptor 
    x86_32_descriptor_init(dest);

    //set the type for ldt
    dest->dword2 |= LDT_DESCRIPTOR_TYPE;

    //set the base
    x86_32_descriptor_set_base(dest , src->base , NULL);

    //set the limit
    err = x86_32_descriptor_set_limit(dest , src->limit , NULL);
    if (err != X86_32_E_OK)
        goto out;

    //set the dpl
    x86_32_descriptor_set_dpl(dest , &src->dpl);

    //set the present
    x86_32_descriptor_set_present(dest , src->present);

out:
    return err;
}