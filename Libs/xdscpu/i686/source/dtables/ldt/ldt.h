#ifndef X86_32_LDT_H
#define X86_32_LDT_H

    #include "../dtables.h"
    #include "../../descriptors/system/ldtd.h"

    struct x86_32_ldt{
        struct x86_32_dtable tbl    ;
        enum x86_32_pl       dpl    ;
        bool                 present;
    };

    x86_32_err_type X86_32_CALL x86_32_ldt_init(
        struct x86_32_ldt*          ldt           ,
        void*                       begin_addr    ,
        void*                       end_addr      ,
        struct _x86_32_descriptor   init_val  
    );

    x86_32_err_type X86_32_CALL x86_32_ldt_set_descriptor(
        struct x86_32_ldt*          ldt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );

    x86_32_err_type X86_32_CALL x86_32_ldt_get_descriptor(
        struct x86_32_ldt*          ldt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );

    void X86_32_CALL x86_32_ldt_set_ldt_descriptor(struct x86_32_ldt_descriptor* dest , const struct x86_32_ldt* src);
    void X86_32_CALL x86_32_ldt_descriptor_set_ldt(struct x86_32_ldt* dest , const struct x86_32_ldt_descriptor* src);

#endif 