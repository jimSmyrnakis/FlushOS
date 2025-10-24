#include "dtables.h"

x86_32_err_type X86_32_CALL x86_32_dtable_init(
    struct x86_32_dtable*       dt            ,
    void*                       begin_addr    ,
    void*                       end_addr      ,
    uint32_t                    max_capacity  ,
    struct _x86_32_descriptor   init_val  
){

    
    x86_32_err_type err = X86_32_E_OK;

    //check if if parameter's get sense
    if ((dt == NULL) || (begin_addr == NULL) || (end_addr == NULL) || (max_capacity == 0)){
        err = X86_32_E_BADPARAM;
        goto out;
    }
    // casting to 32 unsigned int is totaly safe as x86-32 is 32 bit pointer size (memory address is 32 bit)
    uint32_t base = (uint32_t)begin_addr;
    uint32_t end  = (uint32_t)end_addr  ;

    // is base bigger than end ? Then make them in right order
    if (base < end) x86_32_swap(uint32_t , base , end);

    // is the space bigger than two descriptor's ? if not error too small space ()
    if ((end - base + 1) < (2 * sizeof(struct _x86_32_descriptor)) ){
        err = X86_32_E_SMLSPC;
        goto out;
    }

    // if the base is not align to the descriptor size in bytes then return 
    if (base % sizeof(struct _x86_32_descriptor)){
        err = X86_32_E_UNALIGNELMNT;
        goto out;
    }

    //check max capacity parameter and set dt max capacity
    if (max_capacity < sizeof(struct _x86_32_descriptor)){
        err = X86_32_E_BADPARAM;
        goto out;
    }
    dt->max_capacity = max_capacity;

    //if max capacity is not multiple of descriptor size remove some bytes
    if (dt->max_capacity % sizeof(struct _x86_32_descriptor))
        dt->max_capacity -= dt->max_capacity % sizeof(struct _x86_32_descriptor);
    
    //calculate capacity
    dt->capacity = (end - base + 1);

    //if capacity is not multiple of descriptor size remove some bytes
    if (dt->capacity % sizeof(struct _x86_32_descriptor))
        dt->capacity = sizeof(struct _x86_32_descriptor)*(dt->capacity / sizeof(struct _x86_32_descriptor));

    //if capacity is bigger than max_capacity make it equal
    if (dt->capacity > dt->max_capacity) dt->capacity = max_capacity;

    
    //set the base address
    dt->base = (struct _x86_32_descriptor*)begin_addr;

    //initiallize with the init val all the descriptor in the table
    uint32_t i = 0;
    for(i = 0 ; i < x86_32_dtable_size(dt) ; i++)
        dt->base[i] = init_val;
    
    //everything is ok

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_dtable_set_descriptor(
    struct x86_32_dtable*       dt          ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    x86_32_err_type err = X86_32_E_OK;

    //check if index is in range
    if (index >= x86_32_dtable_size(dt)){
        err = X86_32_E_OOR ;
        goto out;
    }

    //check if the param's are not NULL
    if ((dt == NULL) || (desc == NULL)){
        err = X86_32_E_BADPARAM;
        goto out;
    }

    dt->base[index] = (*desc);

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_dtable_get_descriptor(
    struct x86_32_dtable*       dt          ,
    uint16_t                    index       ,
    struct _x86_32_descriptor*  desc 
){
    x86_32_err_type err = X86_32_E_OK;

    //check if index is in range
    if (index >= x86_32_dtable_size(dt)){
        err = X86_32_E_OOR ;
        goto out;
    }

    //check if the param's are not NULL
    if ((dt == NULL) || (desc == NULL)){
        err = X86_32_E_BADPARAM;
        goto out;
    }

    (*desc) = dt->base[index];

out:
    return err;
}























