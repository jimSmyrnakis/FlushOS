#include "selector.h"

#define NULL_SELECTOR ((_x86_32_selector)0x0000)
#define INDEX_MASK    ((_x86_32_selector)0xFFF0)
#define RPL_MASK      ((_x86_32_selector)0x000E)
#define TI            ((_x86_32_selector)0x0001)
#define MAX_INDEX_VAL ((uint16_t)        0x0FFF)

x86_32_err_type X86_32_CALL x86_32_selector_set(_x86_32_selector* dest , const struct x86_32_selector* src){
    //check if index in bounds
    if (src->index > MAX_INDEX_VAL)
        return X86_32_E_OOR;

    //initiallize the system selector value
    (*dest) = NULL_SELECTOR;

    //set the index
    (*dest) |= ((src->index << 4) & INDEX_MASK );

    //set the request privilige level
    uint16_t rpl;
    switch(src->rpl){
        case x86_32_pl_0:rpl = 0;break;
        case x86_32_pl_1:rpl = 1;break;
        case x86_32_pl_2:rpl = 2;break;
        case x86_32_pl_3:rpl = 3;break;
    }
    rpl = rpl << 1;
    (*dest) |= ( rpl & RPL_MASK );

    //set table indicator
    (*dest) |= ((src->ti) ? 0x0001 : 0x0000 );

    return X86_32_E_OK;
}

void X86_32_CALL x86_32_selector_get(struct x86_32_selector* dest , const _x86_32_selector* src){
    
    //initiallize struct
    dest->index = 0     ;
    dest->rpl   = 0     ;
    dest->ti    = false ;

    //set index
    dest->index = ( ((*src) & INDEX_MASK) >> 4 );

    //set rpl
    dest->rpl = ( ( (*src) & RPL_MASK ) >> 1);
    
    //set ti
    dest->ti = ( ((*src) & TI) ? true : false );


}


