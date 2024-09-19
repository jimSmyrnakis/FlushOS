#ifndef X86_32_TASK_GATE32_H
#define X86_32_TASK_GATE32_H

    #include "system.h"

    struct x86_32_task_gate32{
        struct x86_32_selector sel;
        bool                   present;
        enum x86_32_pl         dpl;
    };

    x86_32_err_type X86_32_CALL x86_32_descriptor_set_task_gate32(struct x86_32_task_gate32* dest , const struct _x86_32_descriptor* src);
    x86_32_err_type X86_32_CALL x86_32_descriptor_get_task_gate32(struct _x86_32_descriptor* dest , const struct x86_32_task_gate32* src);

#endif 