#ifndef X86_32_SYSTEM_REGISTERS_H
#define X86_32_SYSTEM_REGISTERS_H

    #include "../../core.h"
    #include "../../error.h"
    #include "../../selector/selector.h"

    typedef struct x86_32_selector x86_32_tr;
    typedef struct x86_32_selector x86_32_ldtr;

    typedef _x86_32_selector _x86_32_tr;
    typedef _x86_32_selector _x86_32_ldtr;

    x86_32_err_type X86_32_CALL x86_32_tr_set  (_x86_32_tr*   dest , const x86_32_tr*   src);
    x86_32_err_type X86_32_CALL x86_32_ldtr_set(_x86_32_ldtr* dest , const x86_32_ldtr* src);

    void X86_32_CALL x86_32_tr_get  (x86_32_tr*   dest , const _x86_32_tr*   src);
    void X86_32_CALL x86_32_ldtr_get(x86_32_ldtr* dest , const _x86_32_ldtr* src);

    extern void X86_32_CALL _x86_32_set_tr(_x86_32_selector* sel);
    extern void X86_32_CALL _x86_32_set_ldtr(_x86_32_selector* sel);

    extern void X86_32_CALL _x86_32_get_tr(_x86_32_selector* sel);
    extern void X86_32_CALL _x86_32_get_ldtr(_x86_32_selector* sel);



#endif 