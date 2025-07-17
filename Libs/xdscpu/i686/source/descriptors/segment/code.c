#include "code.h"
//dword 2 of the descriptor
#define CODE_SEGMENT_S      (X86_32_SET_BIT(uint32_t , 12))
#define CODE_SEGMENT_TYPE   (CODE_SEGMENT_S | X86_32_SET_BIT(uint32_t , 11))
#define CODE_SEGMENT_C      (X86_32_SET_BIT(uint32_t , 10))
#define CODE_SEGMENT_R      (X86_32_SET_BIT(uint32_t ,  9))



x86_32_err_type X86_32_CALL x86_32_descriptor_set_code_segment(struct x86_32_code_segment seg , struct _x86_32_descriptor* desc){
    x86_32_err_type err = X86_32_E_OK;

    
    //check if limit and base are not bigger than the total addresable linear space
    if (x86_32_check_segment_size(seg.base , seg.limit) == false ){
        err =  X86_32_E_SEGMENT_LIMIT_OOB;
        goto out;
    }

    //initiallize the descriptor
    x86_32_descriptor_init(desc);

    //set descriptor type
    desc->dword2 |= CODE_SEGMENT_TYPE;

    //set and check if segment limit is valid value 
    err = x86_32_descriptor_set_limit(desc , seg.limit , NULL);
    if (err != X86_32_E_OK)
        goto out;
    
    //set the base
    x86_32_descriptor_set_base(desc , seg.base , NULL);

    //set conforming bit if need it
    if (seg.conform)
        desc->dword2 |= CODE_SEGMENT_C;

    //set readable bit if need it
    if (seg.readable)
        desc->dword2 |= CODE_SEGMENT_R;

    //set Present bit if need it
    x86_32_descriptor_set_present(desc , seg.present);

    //set supervisor bit if need it
    x86_32_descriptor_set_supervisor(desc , seg.supervisor);

    //set accessed bit if need it
    x86_32_descriptor_set_accessed(desc , seg.accessed);    

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_descriptor_get_code_segment(struct _x86_32_descriptor* desc , struct x86_32_code_segment* seg){
    x86_32_err_type err = X86_32_E_OK;
    

    //check if the descriptor is code segment type
    if (!(desc->dword2 & CODE_SEGMENT_TYPE)){
        err = X86_32_E_INVALID_DESCRIPTOR_TYPE;
        goto out;
    }

    //initiallize the code segment struct
    seg->base       = 0;
    seg->limit      = 0;
    seg->accessed   = false;
    seg->present    = false;
    seg->readable   = false;
    seg->supervisor = false;
    seg->conform    = false;

    //is conforming ?
    if (desc->dword2 & CODE_SEGMENT_C)
        seg->conform = true;
    
    //is accessed ?
    x86_32_descriptor_get_accessed(desc , &seg->accessed);
    
    //is readable ?
    if (desc->dword2 & CODE_SEGMENT_R)
        seg->readable = true;

    //is present ?
    x86_32_descriptor_get_present(desc , &seg->present);

    //is supervisor ?
    x86_32_descriptor_get_supervisor(desc , &seg->supervisor);

    //get the base address (in linear space)
    x86_32_descriptor_get_base(desc , &seg->base);

    //get the limit of the segment
    x86_32_descriptor_get_limit(desc , &seg->limit);

out:
    return err;
}


