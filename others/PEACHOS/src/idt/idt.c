#include "idt.h"

idtDescriptor nullDescriptor(void){
    idtDescriptor d;
    d.attr      = 0;
    d.offset1   = 0;
    d.offset2   = 0;
    d.selector  = 0;
    d.zero      = 0;
    return d;
}

/*
 * Initiallize the table by making a table to point on that entry
 * and setting it's size . If all goes well the function return's 
 * KERNEL_OK , else if size is zero return's ERR_BAD_ARGS value
 */ 
int idtInit(
    idtTable* pTable,
    idtDescriptor* entry ,
    idtDescriptor defaultValue,
    uint16_t  size
){
    error_stat = KERNEL_OK;

    if ((size == 0) || (size > IDT_TABLE_SIZE))
    {
        error_stat = EINVALIDARGS;
        return error_stat;
    }

    pTable->entry = entry;
    pTable->size  = size;

    uint16_t i;
    for(i=0 ; i < size ; i++)
        entry[i] = defaultValue;

    return error_stat;
}
/* 
 * Insert a new descriptor to the table at index position . 
 * If index is out of range , return's ERR_OUT_OF_RANGE else
 * if all ok return's KERNEL_OK
 */
int idtInsertInt(
    uint16_t index,
    idtDescriptor descriptor,
    idtTable* pTable 
){
    error_stat = KERNEL_OK;
    if ((pTable->size == 0) || (pTable->size > IDT_TABLE_SIZE)){
        error_stat = ECORRUPTDATA;
        return error_stat;
    }
    if (index >= pTable->size){
        error_stat = EOUTOFRANGE;
        return error_stat;
    }

    pTable->entry[index] = descriptor;

    return error_stat;
}
/*
 * Removes a descriptor from the table at index position . 
 * If index is out of range , same as insert function .
 */
int idtRemoveInt(
    uint16_t        index   ,
    idtTable*       pTable  ,
    idtDescriptor defaultDescriptor,
    idtDescriptor*  desc
){
    error_stat = KERNEL_OK;
    if ((pTable->size == 0) || (pTable->size > IDT_TABLE_SIZE)){
        error_stat = ECORRUPTDATA;
        return error_stat;
    }
    if (index >= pTable->size){
        error_stat = EOUTOFRANGE;
        return error_stat;
    }

    (*desc) = pTable->entry[index] ;

    pTable->entry[index] = defaultDescriptor;

    return error_stat;
}
/*
 * Creates a new system struct that points to this table 
 * If the table has invalid size return's 
 * 
 */
int idtPointer(
    idtTable table ,
    idtPtr*  ppidt
){
    error_stat = KERNEL_OK;
    if ((table.size == 0) || (table.size > IDT_TABLE_SIZE)){
        error_stat = ECORRUPTDATA;
        return error_stat;
    }

    ppidt->base  = (uint32_t)(table.entry);
    ppidt->limit = (uint16_t)((table.size*sizeof(idtDescriptor)) - 1);

    return error_stat;
}

