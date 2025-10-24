#ifndef __FLUSHOS_PTE_H__
#define __FLUSHOS_PTE_H__

    #include <stdint-gcc.h>
    #include <stddef.h>
    #include <stdbool.h>
    typedef uint32_t pte;

    struct pte_attributes{
        bool present       ; // set if page is present (os defined)
        bool writable      ; // is writable 
        bool user_mode     ; // user access (true) or supervisor (false)
        bool write_through ; // write through (true) caching type or write back (false) ? 
        bool chache_disable; // disable cache for this page 
        bool accessed      ; // is set if pte is accessed during virtual address translation  
        bool dirty         ; // is cpu used this page for write ?

    }; // disabling/enabling caching and write through are effecting only this page

    void set_pte(
        void* page_base, // the physical address of the page that this page table entity points to
        struct pte_attributes attr , 
        pte* entity 
    );

    void get_pte(
        pte* entity ,
        struct pte_attributes* attrs ,
        void** page_base 
    );



#endif 