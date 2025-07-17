#include "idt.h"

#define MAXX (256 * sizeof(struct _x86_32_descriptor) ) 

x86_32_err_type X86_32_CALL x86_32_idt_init(
    struct x86_32_idt*          idt           ,
    void*                       begin_addr    ,
    void*                       end_addr      ,
    struct _x86_32_descriptor   init_val  
){
    return x86_32_dtable_init(&idt->tbl , begin_addr , end_addr , MAXX , init_val);
}

x86_32_err_type X86_32_CALL x86_32_idt_set_descriptor(
    struct x86_32_idt*          idt         ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    return x86_32_dtable_set_descriptor(&idt->tbl , index , desc);
}

x86_32_err_type X86_32_CALL x86_32_idt_get_descriptor(
    struct x86_32_idt*          idt         ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    return x86_32_dtable_get_descriptor(&idt->tbl , index , desc);
}

void X86_32_CALL x86_32_idt_descriptor_set_idt(struct x86_32_idt* dest , const struct _x86_32_idt_descriptor* src){
    dest->tbl.base     = (struct _x86_32_descriptor*)src->base;
    dest->tbl.capacity = src->limit + 1;
    dest->tbl.max_capacity = MAXX;
}



