#ifndef X86_32_CODE_H
#define X86_32_CODE_H

    #include "segment.h"

    struct x86_32_code_segment{
        uint32_t base       ;
        uint32_t limit      ;
        bool     conform    ;
        bool     present    ;
        bool     readable   ;
        bool     supervisor ;
        bool     accessed   ;
    };

    x86_32_err_type X86_32_CALL x86_32_descriptor_set_code_segment(struct x86_32_code_segment seg , struct _x86_32_descriptor* desc);
    x86_32_err_type X86_32_CALL x86_32_descriptor_get_code_segment(struct _x86_32_descriptor* desc , struct x86_32_code_segment* seg);

#endif 
