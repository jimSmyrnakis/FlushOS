#include "ldt.h"

#define MAXX ((uint32_t)0xFFFF + 1)

x86_32_err_type X86_32_CALL x86_32_ldt_init(
    struct x86_32_ldt*          ldt           ,
    void*                       begin_addr    ,
    void*                       end_addr      ,
    struct _x86_32_descriptor   init_val  
){
    return x86_32_dtable_init(&ldt->tbl , begin_addr , end_addr , MAXX , init_val );
}

x86_32_err_type X86_32_CALL x86_32_ldt_set_descriptor(
    struct x86_32_ldt*          ldt         ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    return x86_32_dtable_set_descriptor(&ldt->tbl , index , desc);
}

x86_32_err_type X86_32_CALL x86_32_ldt_get_descriptor(
    struct x86_32_ldt*          ldt         ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    return x86_32_dtable_get_descriptor(&ldt->tbl , index , desc);
}

void X86_32_CALL x86_32_ldt_set_ldt_descriptor(struct x86_32_ldt_descriptor* dest , const struct x86_32_ldt* src){
    dest->base = (uint32_t)src->tbl.base;
    dest->limit = src->tbl.capacity - 1;
    dest->dpl = src->dpl;
    dest->present = src->present;
}

void X86_32_CALL x86_32_ldt_descriptor_set_ldt(struct x86_32_ldt* dest , const struct x86_32_ldt_descriptor* src){
    dest->dpl = src->dpl;
    dest->present = src->present;
    dest->tbl.base = (void*)src->base;
    dest->tbl.capacity = src->limit + 1;
    dest->tbl.max_capacity = MAXX;
}
