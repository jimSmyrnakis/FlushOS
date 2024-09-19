#include "farcalls.h"

x86_32_err_type X86_32_CALL x86_32_far_pointer_set(struct _x86_32_far_pointer* _dest , const struct x86_32_far_pointer* src){
    x86_32_err_type err = X86_32_E_OK;
    
    _dest->_zro = 0;
    _dest->_sel = 0;
    _dest->_ofs = 0;

    err = x86_32_selector_set(&_dest->_sel , &src->selector);
    if (err != X86_32_E_OK)
        goto out;

    _dest->_ofs = (uint32_t)src->procedure;

out:
    return err;
}

void X86_32_CALL x86_32_far_pointer_get(struct x86_32_far_pointer* dest , const struct _x86_32_far_pointer* _src){

    dest->procedure = (void*)_src->_ofs;

    x86_32_selector_get(&dest->selector , &_src->_sel);
    

}