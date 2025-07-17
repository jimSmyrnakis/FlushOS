#ifndef X86_32_TSS32D_H
#define X86_32_TSS32D_H

    #include "system.h"

    struct x86_32_tss32d{
        uint32_t        baseaddr;
        uint32_t        limit   ;
        bool            present ;
        bool            busy    ;
        enum x86_32_pl  dpl     ; 
    };

    x86_32_err_type X86_32_CALL x86_32_descriptor_set_tss32d(struct x86_32_tss32d* dest , const struct _x86_32_descriptor* src);
    x86_32_err_type X86_32_CALL x86_32_descriptor_get_tss32d(struct _x86_32_descriptor* dest , const struct x86_32_tss32d* src);

#endif 