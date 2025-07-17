#include "gdt.h"

#define MAXX ((uint32_t)0xFFFF + 1)

x86_32_err_type X86_32_CALL x86_32_gdt_init(
    struct x86_32_gdt*          gdt           ,
    void*                       begin_addr    ,
    void*                       end_addr      ,
    struct _x86_32_descriptor   init_val  
){
    x86_32_err_type err = X86_32_E_OK;
    
    //call the descriptor table init function
    err = x86_32_dtable_init(&gdt->tbl , begin_addr , end_addr ,MAXX, init_val);
    if (err != X86_32_E_OK)
        goto out;

    //the first element must be set to null descriptor
    x86_32_descriptor_set_null(&gdt->tbl.base[0]);


out:
    return err;
}


x86_32_err_type X86_32_CALL x86_32_gdt_set_descriptor(
    struct x86_32_gdt*          gdt          ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    if (index == 0)
        return X86_32_E_GDTANLDESCR;
    return x86_32_dtable_set_descriptor(&gdt->tbl , index , desc);
}
    
x86_32_err_type X86_32_CALL x86_32_gdt_get_descriptor(
    struct x86_32_gdt*          gdt         ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    return x86_32_dtable_get_descriptor(&gdt->tbl , index , desc );
}

void X86_32_CALL x86_32_gdt_descriptor_set_gdt(struct x86_32_gdt* dest , const struct _x86_32_gdt_descriptor* src){
    dest->tbl.base     = (struct _x86_32_descriptor*)src->base;
    dest->tbl.capacity = src->limit + 1;
    dest->tbl.max_capacity = MAXX;
}
