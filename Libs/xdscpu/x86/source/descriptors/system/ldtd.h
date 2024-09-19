#ifndef X86_32_LDTD_H
#define X86_32_LDTD_H

    #include "system.h"

    struct x86_32_ldt_descriptor{
        uint32_t        base;
        uint32_t        limit;
        bool            present;
        enum x86_32_pl  dpl;
    };

    x86_32_err_type X86_32_CALL x86_32_ldt_descriptor_set(struct x86_32_ldt_descriptor* dest , const struct _x86_32_descriptor* src);
    x86_32_err_type X86_32_CALL x86_32_ldt_descriptor_get(struct _x86_32_descriptor* dest , const struct x86_32_ldt_descriptor* src);


#endif 