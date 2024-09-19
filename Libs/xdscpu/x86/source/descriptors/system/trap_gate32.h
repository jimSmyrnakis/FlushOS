#ifndef X86_32_TRAP_GATE32_H
#define X86_32_TRAP_GATE32_H

    #include "system.h"


    struct x86_32_trap_gate32{ // it doesn't effect the if flag on eflags register
        struct x86_32_selector sel    ;
        void*                  proc   ;
        bool                   present;
        enum x86_32_pl         dpl    ;
    };

    x86_32_err_type X86_32_CALL x86_32_trap_gate32_set(struct x86_32_trap_gate32* dest , const struct _x86_32_descriptor* src);
    x86_32_err_type X86_32_CALL x86_32_trap_gate32_get(struct _x86_32_descriptor* dest , const struct x86_32_trap_gate32* src);

#endif 