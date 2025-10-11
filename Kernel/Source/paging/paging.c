#include "paging.h"
#include "../heap/kheap.h"
#include "../Interrupts/interrupts.h"
//using the classical paging mechanism of 4kb pages


#ifndef NULL
#define NULL ((void*)0)
#endif 
static struct paging_info* current_paging = NULL;

static void paging_flags_to_pte_flags(
    struct paging_flags flags , 
    struct pte_attributes* pte_flags)
{
    pte_flags->chache_disable = flags.cache_disable;
    pte_flags->dirty = flags.dirty;
    pte_flags->present = flags.present;
    pte_flags->user_mode = flags.user;
    pte_flags->write_through = flags.cache_write_through;
    pte_flags->writable = flags.writable;
}

static void paging_flags_to_pde_flags(
    struct paging_flags flags , 
    struct pde_attributes* pde_flags)
{
    pde_flags->chache_disable = flags.cache_disable;
    pde_flags->present = flags.present;
    pde_flags->user_mode = flags.user;
    pde_flags->write_through = flags.cache_write_through;
    pde_flags->writable = flags.writable;
}

struct paging_info* paging_init(struct paging_flags flags){
    struct paging_info* page_table = 
    kmalloc(sizeof(pde) * PAGE_DIR_ENTRIES_CNT);
    if (page_table == NULL)
        return NULL;
        
    pte* allptes = kmalloc(sizeof(pte) * TOTAL_PAGE_TABLES);
    if (allptes == NULL)
    {
        kfree(page_table);
        return NULL;
    }



    page_table->all_ptes = allptes;

    struct pde_attributes pde_common_attrs;
    pde_common_attrs.accessed = false;
    paging_flags_to_pde_flags(flags , &pde_common_attrs);

    struct pte_attributes pte_common_attrs;
    pte_common_attrs.accessed = false;
    paging_flags_to_pte_flags(flags , &pte_common_attrs);
    

    uint32_t physical_page_addr = 0x00000000;
    for (int pde_i = 0; pde_i < PAGE_DIR_ENTRIES_CNT; pde_i++){
        uint32_t* page_table_base =  &allptes[pde_i*PAGE_TBL_ENTRIES_CNT];

        set_pde(
            page_table_base , 
            pde_common_attrs , 
            &page_table->page_dir[pde_i]
        );
        
        for (int pte_i = 0 ; pte_i < PAGE_TBL_ENTRIES_CNT; pte_i++){
            physical_page_addr = 
            pde_i * (PAGE_TBL_ENTRIES_CNT * PHYSICAL_PAGE_SIZE) 
            +   pte_i * PHYSICAL_PAGE_SIZE;
            set_pte(
                (void*)physical_page_addr , 
                pte_common_attrs , 
                &allptes[pde_i*PAGE_TBL_ENTRIES_CNT + pte_i]
            );

        }
         //
    }

    return page_table;
}

void paging_switch(struct paging_info* pinfo){
    disable_intt();
    paging_disable();
    paging_load(pinfo->page_dir);
    current_paging = pinfo;
};

void* paging_get_directory(struct paging_info* pinfo){
    return pinfo->page_dir;
}

bool paging_is_aligned(void* virt){
    return ((uint32_t)virt % PHYSICAL_PAGE_SIZE) == 0;
}

errno paging_get_indexes(void* virt , uint32_t* dir_index , uint32_t* tbl_index){
    uint32_t virt32 = (uint32_t)virt;
    if (!paging_is_aligned(virt))
        return FLUSHOS_EBADARG;

    (*dir_index) = virt32 / (PAGE_TBL_ENTRIES_CNT * PHYSICAL_PAGE_SIZE);
    (*tbl_index) = (virt32 % (PAGE_TBL_ENTRIES_CNT * PHYSICAL_PAGE_SIZE)) / (PHYSICAL_PAGE_SIZE);

    return FLUSHOS_EGOOD;
}

errno paging_set(struct paging_info* pinfo , void* virt , struct page_info * info  ){
    
    uint32_t pde_i , pte_i;
    errno res = paging_get_indexes(virt , &pde_i , &pte_i);
    if (res != FLUSHOS_EGOOD)
        return res;

    struct pte_attributes pte_flags;
    struct pde_attributes pde_flags;
    paging_flags_to_pde_flags(info->flags , &pde_flags);
    paging_flags_to_pte_flags(info->flags , &pte_flags);

    pde* dir = &pinfo->page_dir[pde_i];
    pte* table = &pinfo->all_ptes[pde_i * PAGE_TBL_ENTRIES_CNT + pte_i];
    set_pde(table , pde_flags , dir);
    set_pte(info->phyical_addr , pte_flags , table);

    return FLUSHOS_EGOOD;
}

struct paging_info* paging_get_current(void){
    return current_paging;
}