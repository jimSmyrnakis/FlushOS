#include "virtmem.h"


void virtmem_map(void* virt , void* phys){
    struct page_info page ;
    page.flags.cache_disable = false;
    page.flags.cache_write_through = true;
    page.flags.dirty = false;
    page.flags.present = true;
    page.flags.user = true;
    page.flags.writable = true;
    page.phyical_addr = phys;
    paging_set(paging_get_current() , virt , &page);
}