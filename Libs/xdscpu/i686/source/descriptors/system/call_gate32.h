#ifndef X86_32_CALL_GATE32_H
#define X86_32_CALL_GATE32_H

    #include "system.h"

    struct x86_32_call_gate32{
        void*                   procedure;
        enum x86_32_pl          dpl;
        bool                    present;
        struct x86_32_selector  selector;
        uint8_t                 prmcnt : 4; // parameters count at 32bit multiple sizes
    };

    x86_32_err_type X86_32_CALL x86_32_descriptor_set_call_gate32(struct x86_32_call_gate32* dest , const struct _x86_32_descriptor* src);
    x86_32_err_type X86_32_CALL x86_32_descriptor_get_call_gate32(struct _x86_32_descriptor* dest , const struct x86_32_call_gate32* src);


#endif 