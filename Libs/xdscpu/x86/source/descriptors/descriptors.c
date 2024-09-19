#include "descriptors.h"

#define X86_32_INIT_DESCRIPTOR (X86_32_SET_BIT(uint32_t , 22))

void X86_32_CALL x86_32_descriptor_init(struct _x86_32_descriptor* desc){
    desc->dword1 = 0;
    desc->dword2 = X86_32_INIT_DESCRIPTOR;
}//ok

void X86_32_CALL x86_32_descriptor_set_base(struct _x86_32_descriptor* desc , uint32_t new_base , uint32_t* old_base ){
    // check if old_base pointer is null if no then write old value before clean it
    if (old_base != NULL)
        x86_32_descriptor_get_base(desc , old_base);

    // initiallize base bits to zero
    desc->dword1 &= 0x0000FFFF;
    desc->dword2 &= 0x00FFFF00;

    // write the first 16 bit of the new base to the descriptor (bit0 - bit15)
    desc->dword1 |= ( (new_base & 0x0000FFFF) << 16); 
    // write the next 8 bit (bit16 - bit23)
    desc->dword2 |= ( (new_base & 0x00FF0000) >> 16);
    // write the next 8 last bits (bit24 - bit31)
    desc->dword2 |= ( (new_base & 0xFF000000)      );

}//ok

void X86_32_CALL x86_32_descriptor_get_base(const struct _x86_32_descriptor* desc , uint32_t* base){
    (*base) = 0;
    (*base) =  ( ( desc->dword1 & 0xFFFF0000 ) >> 16)
              |
               ( ( desc->dword2 & 0x000000FF ) << 16)
              | 
               ( ( desc->dword2 & 0xFF000000 ) )
    ;
    
}//ok

#define SET_GRANULARITY (X86_32_SET_BIT(uint32_t , 23))

x86_32_err_type X86_32_CALL x86_32_descriptor_set_limit(struct _x86_32_descriptor* desc , uint32_t new_limit , uint32_t* old_limit){
    
    bool granularity = false;

    //if new_limit bigger or equal than 1MB the must be multyple of 4KB size and granularity be set
    if (new_limit >= (1024*1024)){
        if ((new_limit % 4096) != 0)
            return X86_32_E_SEGMENT_LIMIT_INVALID;
        granularity = true;
    }

    //check for write the old limit before clean it
    if (old_limit == NULL)
        x86_32_descriptor_get_limit(desc , old_limit);

    // initiallize the limit bits to zero
    desc->dword1 &= 0xFFFF0000;
    desc->dword2 &= 0xFFF0FFFF;

    // set granularity if is true and move 12 bits(4KB multyple) (shift) rigth the new_limit value
    if (granularity){
        desc->dword2 |= SET_GRANULARITY;
        new_limit = ( new_limit >> 12 );
    }
    
    // copy the new limit value to the descriptor
    desc->dword1 |= ( ( new_limit & 0x0000FFFF ) );
    desc->dword2 |= ( ( new_limit & 0x000F0000 ) );

    return X86_32_E_OK;
}


void X86_32_CALL x86_32_descriptor_get_limit(const struct _x86_32_descriptor* desc , uint32_t* limit){
    
    (*limit) = ((desc->dword1 & 0x0000FFFF) | (desc->dword2 & 0x000F0000) );
    
    if (desc->dword2 & SET_GRANULARITY)
        (*limit) = ((*limit) << 12);
    
}

#define SET_PRESENT (X86_32_SET_BIT(uint32_t , 15))

void X86_32_CALL x86_32_descriptor_set_present(struct _x86_32_descriptor* desc , bool present){
    if (present)
        desc->dword2 |= SET_PRESENT;
    else
        desc->dword2 &= ~SET_PRESENT; 
}

void X86_32_CALL x86_32_descriptor_get_present(const struct _x86_32_descriptor* desc , bool* present){
    (*present) = (desc->dword2 & SET_PRESENT);
}

#define SET_USER (X86_32_SET_BIT(uint32_t , 14) | X86_32_SET_BIT(uint32_t , 13))

void X86_32_CALL x86_32_descriptor_set_supervisor(struct _x86_32_descriptor* desc , bool supervisor ){
    if (!supervisor)
        desc->dword2 |= SET_USER;
    else
        desc->dword2 &= ~SET_USER; 
}
void X86_32_CALL x86_32_descriptor_get_supervisor(const struct _x86_32_descriptor* desc , bool* supervisor){
    (*supervisor) = !(desc->dword2 & SET_USER);
}

#define SET_ACCESSED (X86_32_SET_BIT(uint32_t ,  8))

void X86_32_CALL x86_32_descriptor_set_accessed(struct _x86_32_descriptor* desc , bool  accessed){
    if (!accessed)
        desc->dword2 |= SET_ACCESSED;
    else
        desc->dword2 &= ~SET_ACCESSED; 
}

void X86_32_CALL x86_32_descriptor_get_accessed(const struct _x86_32_descriptor* desc , bool* accessed){
    (*accessed) = (desc->dword2 & SET_ACCESSED);
}

#define SELECTOR_MASK ((uint32_t) 0xFFFF0000) // dword 1

void X86_32_CALL x86_32_descriptor_set_selector(struct _x86_32_descriptor* dest , const _x86_32_selector* src){
    dest->dword1 &= ~SELECTOR_MASK;
    dest->dword1 |= ( SELECTOR_MASK & ( ((uint32_t)(*src)) << 16) );  
}
void X86_32_CALL x86_32_descriptor_get_selector(_x86_32_selector* dest , const struct _x86_32_descriptor* src){
    (*dest) = ( (src->dword1 & SELECTOR_MASK) >> 16);
}

#define DPL_MASK ((uint32_t) 0x00006000)
#define DPL_0    ((uint32_t) 0x00000000)
#define DPL_1    ((uint32_t) 0x00002000)
#define DPL_2    ((uint32_t) 0x00003000)
#define DPL_3    DPL_MASK

void X86_32_CALL x86_32_descriptor_set_dpl(struct _x86_32_descriptor* dest , const enum x86_32_pl* src){
    dest->dword2 &= !DPL_MASK;

    switch(*src){
        case x86_32_pl_0: dest->dword2 |= DPL_0; break;
        case x86_32_pl_1: dest->dword2 |= DPL_1; break;
        case x86_32_pl_2: dest->dword2 |= DPL_2; break;
        case x86_32_pl_3: dest->dword2 |= DPL_3; break;
    }
}
void X86_32_CALL x86_32_descriptor_get_dpl(enum x86_32_pl* dest , const struct _x86_32_descriptor* src){
    (*dest) = x86_32_pl_0;

    switch(src->dword2 & DPL_MASK){
        case DPL_0: (*dest) = x86_32_pl_0; break;
        case DPL_1: (*dest) = x86_32_pl_1; break;
        case DPL_2: (*dest) = x86_32_pl_2; break;
        case DPL_3: (*dest) = x86_32_pl_3; break;
    }
}

void X86_32_CALL x86_32_descriptor_set_null(struct _x86_32_descriptor* desc){
    x86_32_descriptor_init(desc);
}

void X86_32_CALL x86_32_descriptor_set_offset(struct _x86_32_descriptor* dest , const uint32_t* src){
    dest->dword1 &= 0xFFFF0000;
    dest->dword2 &= 0x0000FFFF;

    dest->dword1 |= ((*src) & 0x0000FFFF);
    dest->dword2 |= ((*src) & 0xFFFF0000);
}
void X86_32_CALL x86_32_descriptor_get_offset(uint32_t* dest , const struct _x86_32_descriptor* src){
    (*dest) = 0;

    (*dest) |= (src->dword1 & 0x0000FFFF);
    (*dest) |= (src->dword2 & 0xFFFF0000);
}
