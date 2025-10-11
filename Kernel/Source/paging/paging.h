#ifndef __FLUSHOS_PAGING_H__
#define __FLUSHOS_PAGING_H__

    
    #include "pte.h"
    #include "pde.h"
    #include "../errno.h"
    #define PAGE_DIR_ENTRIES_CNT 1024 // the number of all paging directory entries
    #define PAGE_TBL_ENTRIES_CNT 1024 // the number of all paging table entries
    #define TOTAL_PAGE_TABLES PAGE_DIR_ENTRIES_CNT * PAGE_TBL_ENTRIES_CNT // the number of total page tables in all
    #define PHYSICAL_PAGE_SIZE 4096 // the size in bytes of each physical page 
    
    extern void paging_enable(void);
    extern void paging_disable(void);
    extern void paging_load(void* dt_physical_address);

    

    struct paging_info 
    {
        pde* page_dir ; // for moment that all we need 
        pte* all_ptes ;
    };

    struct paging_flags{
        bool user;
        bool dirty;
        bool writable;
        bool cache_disable;
        bool cache_write_through;
        bool present;
    };

    

    struct paging_info* paging_init(struct paging_flags flags);

    void paging_switch(struct paging_info* pinfo);

    void* paging_get_directory(struct paging_info* pinfo);

    bool paging_is_aligned(void* virt);
    errno paging_get_indexes(void* virt , uint32_t* dir_index , uint32_t* tbl_index);


    struct page_info {
        void* phyical_addr;
        struct paging_flags flags;
    };

    errno paging_set(struct paging_info* pinfo , void* virt , struct page_info * info  );
    struct paging_info* paging_get_current(void);
#endif 