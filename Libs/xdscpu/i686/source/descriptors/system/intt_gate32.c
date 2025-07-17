#include "intt_gate32.h"

#define INTT_GATE32_TYPE    ((uint32_t) 0x00000F00)

x86_32_err_type X86_32_CALL x86_32_intt_gate32_set(struct x86_32_intt_gate32* dest , const struct _x86_32_descriptor* src){
    x86_32_err_type err = X86_32_E_OK;

    //check if type is the right one
    if ( (src->dword2 & INTT_GATE32_TYPE) != INTT_GATE32_TYPE ){
        err = X86_32_E_INVALID_DESCRIPTOR_TYPE;
        goto out;
    }

    //if type is right one then take selector system value and make it to a struct selector
    _x86_32_selector ssel;//system selector value
    x86_32_descriptor_get_selector(&ssel , src); // read the value
    x86_32_selector_get(&dest->sel , &ssel); // take it as struct selector to the struct intt gate32 descriptor 

    // take if is present
    x86_32_descriptor_get_present(src , &dest->present);

    // take the dpl
    x86_32_descriptor_get_dpl(&dest->dpl , src);

    //and last , take the procedure/offset
    uint32_t proc;
    x86_32_descriptor_get_offset(&proc , src);
    dest->proc = (void*)proc;

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_intt_gate32_get(struct _x86_32_descriptor* dest , const struct x86_32_intt_gate32* src){
    x86_32_err_type err = X86_32_E_OK;

    //initiallize the descriptor
    x86_32_descriptor_init(dest);

    //set the correct type
    dest->dword2 |= INTT_GATE32_TYPE;

    //take the selector struct and make it to a system selector value
    _x86_32_selector ssel; //system selector
    err = x86_32_selector_set(&ssel , &src->sel); // get the system selector value
    if (err != X86_32_E_OK)
        goto out;
    x86_32_descriptor_set_selector(dest , &ssel); // paste it to the system descriptor value 

    //set present
    x86_32_descriptor_set_present(dest , src->present);

    //set dpl
    x86_32_descriptor_set_dpl(dest , &src->dpl);

    //set procedure
    uint32_t proc = (uint32_t)src->proc;
    x86_32_descriptor_set_offset(dest , &proc);

    //everything is set
out:

    return err;
}