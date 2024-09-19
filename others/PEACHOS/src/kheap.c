#include "kheap.h"

static void* table ;
static uint32_t limit ;
static void* hStart ;
static uint32_t hLimit ;
static HeapHandler hHandler;

void initKernelHeap(void){
    table = PEACHOS_HTABLE_START_ADDRESS;
    limit = PEACHOS_HEAP_SIZE / HEAP_BLOCK_BYTES - 1;
    hStart = PEACHOS_HEAP_START_ADDRESS;
    hLimit = PEACHOS_HEAP_SIZE - 1 ;
    loadHeapTable(table , limit , hStart , hLimit , &hHandler );
}

void* kmalloc(uint32_t count){
    
    if ( count % HEAP_BLOCK_BYTES){
        count = ((count/HEAP_BLOCK_BYTES) * HEAP_BLOCK_BYTES ) + HEAP_BLOCK_BYTES;
    }
    
    void* mem = KNULL;
    uint8_t res = 0;
    res = allocateMem(&hHandler , count/HEAP_BLOCK_BYTES , &mem  );
    if (res != KERNEL_OK)
        mem = KNULL;
    return mem;
}

void* kzalloc(uint32_t count){
    uint8_t* res = (uint8_t*)kmalloc(count);
    if (res == KNULL)
        return KNULL;
    
    if ( count % HEAP_BLOCK_BYTES)
        count = ((count/HEAP_BLOCK_BYTES) * HEAP_BLOCK_BYTES ) + HEAP_BLOCK_BYTES;
    
    
    uint32_t i ;
    for (i = 0 ; i < count ; i++ )
        res[i] = 0;
    

    return res;
}




void  kfree(void* ptr){
    dallocateMem(&hHandler , ptr);
}