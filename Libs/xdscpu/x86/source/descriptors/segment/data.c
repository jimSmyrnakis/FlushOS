#include "data.h"

//dword 2 of the descriptor
#define DATA_SEGMENT_TYPE   (X86_32_SET_BIT(uint32_t , 12))
#define DATA_SEGMENT_W      (X86_32_SET_BIT(uint32_t ,  9))

x86_32_err_type X86_32_CALL x86_32_descriptor_set_data_segment(struct x86_32_data_segment seg , struct _x86_32_descriptor* desc){
    x86_32_err_type err = X86_32_E_OK;

    //check if segment base and limit is out of bounds
    if (x86_32_check_segment_size(seg.base , seg.limit) == false ){
        err =  X86_32_E_SEGMENT_LIMIT_OOB;
        goto out;
    }

    //initiallized descriptor
    x86_32_descriptor_init(desc);

    //set descriptor data segment type
    desc->dword2 = DATA_SEGMENT_TYPE;

    //set descriptor limit
    err = x86_32_descriptor_set_limit(desc , seg.limit , X86_32_NULL);
    if (err != X86_32_E_OK) goto out;

    //set descriptor base
    x86_32_descriptor_set_base(desc , seg.base , X86_32_NULL);

    //set descriptor present
    x86_32_descriptor_set_present(desc , seg.present);

    //set descriptor supervisor
    x86_32_descriptor_set_supervisor(desc , seg.supervisor);

    //set data segment descriptor accessed
    x86_32_descriptor_set_accessed(desc , seg.accessed);

    //set data segment descriptor as writable
    if (seg.writable)
        desc->dword2 |= DATA_SEGMENT_W;


out:
    return err;
}


x86_32_err_type X86_32_CALL x86_32_descriptor_get_data_segment(struct _x86_32_descriptor* desc , struct x86_32_data_segment* seg){
    x86_32_err_type err = X86_32_E_OK;
    

    //check if the descriptor is code segment type
    if (!(desc->dword2 & DATA_SEGMENT_TYPE)){
        err = X86_32_E_INVALID_DESCRIPTOR_TYPE;
        goto out;
    }

    //initiallize the code segment struct
    seg->base       = 0;
    seg->limit      = 0;
    seg->accessed   = false;
    seg->present    = false;
    seg->writable   = false;
    seg->supervisor = false;
    
    //get the base address (in linear space)
    x86_32_descriptor_get_base(desc , &seg->base);

    //get the limit of the segment
    x86_32_descriptor_get_limit(desc , &seg->limit);

    //is present ?
    x86_32_descriptor_get_present(desc , &seg->present);

    //is accessed ?
    x86_32_descriptor_get_accessed(desc , &seg->accessed);

    //is supervisor ?
    x86_32_descriptor_get_supervisor(desc , &seg->supervisor);

    //is writable ?
    if (desc->dword2 & DATA_SEGMENT_W)
        seg->writable = true;

out:
    return err;
}

