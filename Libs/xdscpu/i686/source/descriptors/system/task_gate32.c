#include "task_gate32.h"

#define TASK_GATE32_TYPE ((uint32_t) 0x00000500)

x86_32_err_type X86_32_CALL x86_32_descriptor_set_task_gate32(struct x86_32_task_gate32* dest , const struct _x86_32_descriptor* src){
    x86_32_err_type err = X86_32_E_OK;

    //check if type is right
    if ((src->dword2 & TASK_GATE32_TYPE) != TASK_GATE32_TYPE ){
        err = X86_32_E_INVALID_DESCRIPTOR_TYPE;
        goto out;
    }

    //get selector
    _x86_32_selector val;
    x86_32_descriptor_get_selector(&val , src);
    x86_32_selector_get(&dest->sel , &val);

    //get dpl
    x86_32_descriptor_get_dpl(&dest->dpl , src);

    //get present
    x86_32_descriptor_get_present(src , &dest->present);

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_descriptor_get_task_gate32(struct _x86_32_descriptor* dest , const struct x86_32_task_gate32* src){

    x86_32_err_type err = X86_32_E_OK;

    //initiallize descriptor
    x86_32_descriptor_init(dest);

    //set selector
    _x86_32_selector val;
    err = x86_32_selector_set(&val, &src->sel);
    if (err != X86_32_E_OK)
        goto out;
    x86_32_descriptor_set_selector(dest , &val);

    //set dpl
    x86_32_descriptor_set_dpl(dest , &src->dpl);

    //set present
    x86_32_descriptor_set_present(dest , src->present);


out:
    return err;
}

