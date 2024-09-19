#include "system.h"

x86_32_err_type X86_32_CALL x86_32_tr_set  (_x86_32_tr*   dest , const x86_32_tr*   src) { return x86_32_selector_set(dest , src); }
x86_32_err_type X86_32_CALL x86_32_ldtr_set(_x86_32_ldtr* dest , const x86_32_ldtr* src) { return x86_32_selector_set(dest , src); }

void X86_32_CALL x86_32_tr_get  (x86_32_tr*   dest , const _x86_32_tr*   src) { return x86_32_selector_get(dest , src); }
void X86_32_CALL x86_32_ldtr_get(x86_32_ldtr* dest , const _x86_32_ldtr* src) { return x86_32_selector_get(dest , src); }

