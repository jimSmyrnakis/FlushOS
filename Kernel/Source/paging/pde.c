#include "pde.h"

#define PRESENT         ((pde)0x00000001)
#define WRITABLE        ((pde)0x00000002)
#define USER            ((pde)0x00000004)
#define WRITE_THROUGH   ((pde)0x00000008)
#define CACHE_DISABLE   ((pde)0x00000010)
#define ACCESSED        ((pde)0x00000020)
#define BASE_MASK       ((pde)0xFFFFF000) 

void set_pde(
    void* page_table_base, // the physical address of the page table that this page directory entity points to
    struct pde_attributes attr , 
    pde* entity 
){
    uintptr_t pte_base = (uintptr_t)page_table_base;
    (*entity) = BASE_MASK & pte_base; // initiallize it
    (*entity) |= attr.present           ? PRESENT       : 0;
    (*entity) |= attr.writable          ? WRITABLE      : 0;
    (*entity) |= attr.user_mode         ? USER          : 0;
    (*entity) |= attr.write_through     ? WRITE_THROUGH : 0;
    (*entity) |= attr.chache_disable    ? CACHE_DISABLE : 0;
    (*entity) |= attr.accessed          ? ACCESSED      : 0;
}

#define is_flags_set(val , flags) ( ((val) & (flags)) == (flags))

void get_pde(
    pde* entity ,
    struct pde_attributes* attrs ,
    void** page_table_base 
){
    
    (*page_table_base)      = (void*)((*entity) & BASE_MASK);
    attrs->present          = is_flags_set(*entity , PRESENT)        ? true : false;
    attrs->writable         = is_flags_set(*entity , WRITABLE)       ? true : false;
    attrs->user_mode        = is_flags_set(*entity , USER)           ? true : false;
    attrs->write_through    = is_flags_set(*entity , WRITE_THROUGH)  ? true : false;
    attrs->chache_disable   = is_flags_set(*entity , CACHE_DISABLE)  ? true : false;
    attrs->accessed         = is_flags_set(*entity , ACCESSED)       ? true : false;

}