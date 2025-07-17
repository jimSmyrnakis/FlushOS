#include "segment.h"


x86_32_err_type X86_32_CALL x86_32_cs_set(_x86_32_cs* dest , const x86_32_cs* src) { return x86_32_selector_set(dest , src); }
x86_32_err_type X86_32_CALL x86_32_ds_set(_x86_32_ds* dest , const x86_32_ds* src) { return x86_32_selector_set(dest , src); }
x86_32_err_type X86_32_CALL x86_32_ss_set(_x86_32_ss* dest , const x86_32_ss* src) { return x86_32_selector_set(dest , src); }
x86_32_err_type X86_32_CALL x86_32_fs_set(_x86_32_fs* dest , const x86_32_fs* src) { return x86_32_selector_set(dest , src); }
x86_32_err_type X86_32_CALL x86_32_gs_set(_x86_32_gs* dest , const x86_32_gs* src) { return x86_32_selector_set(dest , src); }


void X86_32_CALL x86_32_cs_get(x86_32_cs* dest , const _x86_32_cs* src) { return x86_32_selector_get(dest , src); }
void X86_32_CALL x86_32_ds_get(x86_32_ds* dest , const _x86_32_ds* src) { return x86_32_selector_get(dest , src); }
void X86_32_CALL x86_32_ss_get(x86_32_ss* dest , const _x86_32_ss* src) { return x86_32_selector_get(dest , src); }
void X86_32_CALL x86_32_fs_get(x86_32_fs* dest , const _x86_32_fs* src) { return x86_32_selector_get(dest , src); }
void X86_32_CALL x86_32_gs_get(x86_32_gs* dest , const _x86_32_gs* src) { return x86_32_selector_get(dest , src); }

