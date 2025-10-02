#ifndef __FLUSHOS_HEAP_H__
#define __FLUSHOS_HEAP_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include "../errno.h"

    typedef uint32_t uiptr;

    struct heap_attr{
        uint16_t block_size; // The size on bytes of each block on the heap 
        uiptr    base      ; // The start address for the heap
        uiptr    size      ; // the size in bytes of the available addressing space 
    }; // this heap allocator does not check things as where ram physical addresses
    // are that will given by the user (kernel main) :)

    struct heap_info{
        uint16_t blck_size;  // The size of the block in bytes 
        uiptr    base     ;  // The actual base address that have been given
        uiptr    size     ;  // The actual size in bytes of the estimate by the user available space
        uiptr    heap_base;  // The base address where the user heap starts
        uiptr    heap_size;  // The heap actual size in bytes without that of the system required
        uiptr    syst_base;  // The actually system structures start address 
        uint16_t syst_size;  // The actual system structures size in bytes
        uint32_t avai_blks;  // The number of blocks that is available at that moment
    };

    

    struct heap{

        void* sys_data; // This pointer refernces to heap system data structures
        // that must not be used and is for the heap system only 
        struct heap_info* info; // This structure is updated every time by the heap system 
        // with the new state of the heap  
    }  ; // This struct is used as a indetifier to our heap and is different for each
    // heap . The reason sys_data is a void* pointer is because the implementation and 
    // algorithm structures of the heap may change in the future

    errno heap_create(struct heap_attr attr , struct heap** heap);
    // Creates the heap , system structures and stuff 

    struct heap_info heap_get_info(struct heap* id);
    // Get all info of the heap at the current state

    void* heap_malloc(struct heap* id , size_t size);
    // Allocate a block of memory from this heap , return's null if there is no space available
    // or the new block/blocks base address

    void* heap_zalloc(struct heap* id , size_t size);
    // same with heap_malloc but all data are zero value

    bool  heap_free(struct heap* id , void* ptr);
    // free this block/blocks based on the address and heap system structures 
    // as well as the malloc usage for this address to be in space of the allocated
    // blocks . Return's true if succeded and false if this address does not fall in
    // any allocated block :)


#endif 
