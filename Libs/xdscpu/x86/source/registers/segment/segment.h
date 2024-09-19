#ifndef X86_32_SEGMENT_REGISTERS_H
#define X86_32_SEGMENT_REGISTERS_H

    #include "../../core.h"
    #include "../../error.h"
    #include "../../selector/selector.h"

    typedef struct x86_32_selector x86_32_cs ;
    typedef struct x86_32_selector x86_32_ds ;
    typedef struct x86_32_selector x86_32_ss ;
    typedef struct x86_32_selector x86_32_fs ;
    typedef struct x86_32_selector x86_32_gs ;
    
    typedef _x86_32_selector _x86_32_cs ;
    typedef _x86_32_selector _x86_32_ds ;
    typedef _x86_32_selector _x86_32_ss ;
    typedef _x86_32_selector _x86_32_fs ;
    typedef _x86_32_selector _x86_32_gs ;

    x86_32_err_type X86_32_CALL x86_32_cs_set(_x86_32_cs* dest , const x86_32_cs* src);
    x86_32_err_type X86_32_CALL x86_32_ds_set(_x86_32_ds* dest , const x86_32_ds* src);
    x86_32_err_type X86_32_CALL x86_32_ss_set(_x86_32_ss* dest , const x86_32_ss* src);
    x86_32_err_type X86_32_CALL x86_32_fs_set(_x86_32_fs* dest , const x86_32_fs* src);
    x86_32_err_type X86_32_CALL x86_32_gs_set(_x86_32_gs* dest , const x86_32_gs* src);

    void X86_32_CALL x86_32_cs_get(x86_32_cs* dest , const _x86_32_cs* src);
    void X86_32_CALL x86_32_ds_get(x86_32_ds* dest , const _x86_32_ds* src);
    void X86_32_CALL x86_32_ss_get(x86_32_ss* dest , const _x86_32_ss* src);
    void X86_32_CALL x86_32_fs_get(x86_32_fs* dest , const _x86_32_fs* src);
    void X86_32_CALL x86_32_gs_get(x86_32_gs* dest , const _x86_32_gs* src);

    extern void X86_32_CALL _x86_32_set_cs(_x86_32_cs* sel);
    extern void X86_32_CALL _x86_32_set_ds(_x86_32_ds* sel);
    extern void X86_32_CALL _x86_32_set_ss(_x86_32_ss* sel);
    extern void X86_32_CALL _x86_32_set_fs(_x86_32_fs* sel);
    extern void X86_32_CALL _x86_32_set_gs(_x86_32_gs* sel);

    extern void X86_32_CALL _x86_32_get_cs(_x86_32_cs* sel);
    extern void X86_32_CALL _x86_32_get_ds(_x86_32_ds* sel);
    extern void X86_32_CALL _x86_32_get_ss(_x86_32_ss* sel);
    extern void X86_32_CALL _x86_32_get_fs(_x86_32_fs* sel);
    extern void X86_32_CALL _x86_32_get_gs(_x86_32_gs* sel);




#endif 