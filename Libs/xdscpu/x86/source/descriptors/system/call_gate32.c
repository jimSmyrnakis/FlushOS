#include "call_gate32.h"

#define CALL_GATE32_TYPE     ((uint32_t) 0x00000C00) // dword 2
#define PROC_00_15           ((uint32_t) 0x0000FFFF) // dword 1
#define PROC_16_31           ((uint32_t) 0xFFFF0000) // dword 2
#define PARAM_COUNT          ((uint32_t) 0x0000000F) // dword 2

x86_32_err_type X86_32_CALL x86_32_descriptor_set_call_gate32(struct x86_32_call_gate32* dest , const struct _x86_32_descriptor* src){
    x86_32_err_type err = X86_32_E_OK;
    
    //check if type is right
    if ( (src->dword2 & CALL_GATE32_TYPE) == CALL_GATE32_TYPE ){
        err = X86_32_E_INVALID_DESCRIPTOR_TYPE;
        goto out;
    }

    //get dpl
    x86_32_descriptor_get_dpl(&dest->dpl , src);

    //get parameters count
    dest->prmcnt = (src->dword2 & PARAM_COUNT);

    //get present
    x86_32_descriptor_get_present(src , &dest->present);

    //get procedure 15 first bits
    dest->procedure = (void*)(( src->dword1 & PROC_00_15 ) | ( src->dword2 & PROC_16_31 ) );

    //get selector
    _x86_32_selector val;
    x86_32_descriptor_get_selector(&val , src);
    x86_32_selector_get(&dest->selector , &val);
    

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_descriptor_get_call_gate32(struct _x86_32_descriptor* dest , const struct x86_32_call_gate32* src){

    x86_32_err_type err = X86_32_E_OK;
    
    //initiallize descriptor
    x86_32_descriptor_init(dest);

    //set type
    dest->dword2 |= CALL_GATE32_TYPE;

    //set present
    x86_32_descriptor_set_present(dest , src->present);

    //set dpl
    x86_32_descriptor_set_dpl(dest , &src->dpl);

    //set procedure
    dest->dword1 |= (((uint32_t)src->procedure) & 0x0000FFFF);
    dest->dword2 |= ((uint32_t)(src->procedure) & 0xFFFF0000);

    //set selector
    _x86_32_selector val;
    x86_32_selector_set(&val , &src->selector);
    dest->dword1 |= (((uint32_t)val) << 16 );

    //set parameter count
    dest->dword2 |= (src->prmcnt & 0x0000000F);

out:
    return err;
}