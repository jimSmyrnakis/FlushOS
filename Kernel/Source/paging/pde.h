#ifndef __FLUSHOS_PDE_H__
#define __FLUSHOS_PDE_H__

    #include <stdint-gcc.h>
    #include <stddef.h>
    #include <stdbool.h>
    typedef uint32_t pde;

    struct pde_attributes{
        bool present       ; // set if page dir entity is present (os defined)
        bool writable      ; // is writable 
        bool user_mode     ; // user access (true) or supervisor (false)
        bool write_through ; // write through (true) caching type or write back (false) ? happens in all 4MB memory package
        bool chache_disable; // disable cache , disable it for all 4MB memory package 
        bool accessed      ; // is set if pde is accessed during virtual address translation  
    }; // disabling/enabling caching and write through are effecting all the pages of the paging table :)


    void set_pde(
        void* page_table_base, // the physical address of the page table that this page directory entity points to
        struct pde_attributes attr , 
        pde* entity 
    );

    void get_pde(
        pde* entity ,
        struct pde_attributes* attrs ,
        void** page_table_base 
    );



#endif 