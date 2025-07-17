#ifndef X86_32_INTT_GATE32_H
#define X86_32_INTT_GATE32_H

    #include "system.h"


    struct x86_32_intt_gate32{ // it clears if flag on eflags register
        struct x86_32_selector sel    ;
        void*                  proc   ;
        bool                   present;
        enum x86_32_pl         dpl    ;
    };

    x86_32_err_type X86_32_CALL x86_32_intt_gate32_set(struct x86_32_intt_gate32* dest , const struct _x86_32_descriptor* src);
    x86_32_err_type X86_32_CALL x86_32_intt_gate32_get(struct _x86_32_descriptor* dest , const struct x86_32_intt_gate32* src);

#endif 