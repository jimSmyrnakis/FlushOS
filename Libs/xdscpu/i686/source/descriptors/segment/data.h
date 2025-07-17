#ifndef X86_32_DATA_H
#define X86_32_DATA_H

    #include "segment.h"

    struct x86_32_data_segment{
        uint32_t base       ;
        uint32_t limit      ;
        bool     present    ;
        bool     writable   ;
        bool     supervisor ;
        bool     accessed   ;
    };


    x86_32_err_type X86_32_CALL x86_32_descriptor_set_data_segment(struct x86_32_data_segment seg , struct _x86_32_descriptor* desc );
    x86_32_err_type X86_32_CALL x86_32_descriptor_get_data_segment(struct _x86_32_descriptor* desc , struct x86_32_data_segment* seg);

#endif 