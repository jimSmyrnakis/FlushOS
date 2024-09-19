#ifndef HEAP_H
#define HEAP_H

    #include <status.h>
    #include <config.h>
    #include <def.h>

    #define ET0         0b00000001
    #define ET1         0b00000010
    #define ET2         0b00000100
    #define ET3         0b00001000
    #define FIRST       0b01000000
    #define HAS_NEXT    0b10000000
    #define BLOCK_TAKEN ET0 
    #define HEAP_BLOCK_BYTES 4096

    typedef uint8_t HeapDescriptor;

    struct HeapHandler{
        HeapDescriptor* table;
        uint32_t        size ;
        void*           base ;
        uint32_t        limit;
    };
    typedef struct HeapHandler HeapHandler;

    int loadHeapTable(
        void*       tableBaseAddress  ,
        uint32_t    tableLimit ,
        void*       heapBaseAddress   ,
        uint32_t    heapLimit  ,
        HeapHandler* heap      
    );
    /*
     * Load on heap handler the heap table base and limit (tableBaseAddress/Limit)
     * Load on heap handler the heap base and limit (heapBaseAddress/Limit)
     * return's the :
     * 1. KERNEL_OK    => when heap handler initiallized
     * 2. ENOTALLIGN   => when heapBaseAddress or heapLimit is not allign to 4096 
     * 3. EINVALIDARGS => when caculated heap table and heap sizes are different
     */

    int allocateMem(
        HeapHandler* heap ,
        uint16_t     blocksCount,
        void**       mem  
    );
    /*
     * Using the specific heap handler this function can allocate 
     * blocks of 4096 bytes long each . The heap param is the heapHandler
     * that contain the heap Table and the heap base and limit addresses.
     * Parameter mem is a double void pointer that make the first layer 
     * pointer point to the allocated blocks that have been provided . In
     * Some situations mem may have an undefined value so the compination
     * of the return value and of the mem can say if there is space or errors.
     * More specific this function return's :
     *  1. KERNEL_OK     => mem has the base address that have been allocated
     *  2. ECORRUPTDATA  => heap table size and heap limit are not equal
     *  3. ENOTALLIGN    => heap base and limit are not alligned to 4096
     *  4. EOUTOFRANGE   => blocksCount is greater that heap size
     *  5. ENOMEMORY     => if no memory found for this request
     */

    int dallocateMem(
        HeapHandler* heap ,
        void*        mem  
    );
    /*
     * Using the specific heap handler and mem void pointer , this function
     * free the allocated blocks of heap memory . The heap param is the 
     * heapHandler that contain the heap Table and the heap base and limit
     * addresses. Parameter mem has the first block address for the allocated
     * blocks provided using the allocateMem(...) . Is very strict about the 
     * address provides the mem pointer . More specific this function return's:
     *   1. KERNEL_OK     => the blocks from the call of allocation are freed
     *   2. ECORRUPTDATA  => heap table size and heap limit are not equal
     *   3. ENOTALLIGN    => heap base/limit or mem pointer are not alligned to 4096
     *   4. EOUTOFRANGE   => mem address not in bounds of the heap
     *   5. EINVALIDARGS  => if the mem address is not the first block 
     * Finally , this function return's KERNEL_OK even the address block 
     * we ask to free is already freed . 
    */






#endif 