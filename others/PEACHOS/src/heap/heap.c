#include "heap.h"

#define isAllign(addr) (((addr)%HEAP_BLOCK_BYTES) == 0 )
#define isTaken(hdesc) (((hdesc) & BLOCK_TAKEN) == BLOCK_TAKEN)
#define isFirst(hdesc) (((hdesc) & FIRST) == FIRST)
#define hasNext(hdesc) (((hdesc) & HAS_NEXT) == HAS_NEXT)
#define memoryToIndex(mem , base) (((((uint32_t)mem) - ((uint32_t)base))/HEAP_BLOCK_BYTES))

int loadHeapTable(
    void*       tableBaseAddress  ,
    uint32_t    tableLimit ,
    void*       heapBaseAddress   ,
    uint32_t    heapLimit ,
    HeapHandler* heap      
){
    
    int i;

    error_stat = KERNEL_OK;
    // check if all addresses are alligned to 4096 
    if ((!isAllign((uint32_t)heapBaseAddress)) || (!isAllign(heapLimit + 1))){
        error_stat = ENOTALLIGN;
        return error_stat;
    }

    // check if heap table size and heap size are equal
    if ((tableLimit+1) !=  ((heapLimit + 1) / HEAP_BLOCK_BYTES) ){
        error_stat = EINVALIDARGS;
        return error_stat;
    }
        
    
    // we know now that everything ok so heap handler initiallize set
    // and initiallize the heap table

    heap->table = tableBaseAddress;
    heap->size  = tableLimit + 1;
    heap->base  = heapBaseAddress;
    heap->limit = heapLimit;

    for(i = 0; i < heap->size ; i++){
        heap->table[i] = 0;
    }

    return error_stat;
}

int allocateMem(
    HeapHandler* heap ,
    uint16_t     blocksCount,
    void**        mem  
){
    error_stat = KERNEL_OK;

    //check if heap size and heap Table size are relative equal
    if (heap->size != ((heap->limit+1)/HEAP_BLOCK_BYTES)){
        error_stat = ECORRUPTDATA;
        return error_stat;
    }

    // check if everything is alligned
    if (
        (!isAllign((uint32_t)heap->base)) 
        || 
        (!isAllign((uint32_t)heap->limit + 1))
    ){
        error_stat = ENOTALLIGN;
        return error_stat;
    }

    // check if we are in bounds
    if (blocksCount > heap->size){
        error_stat = EOUTOFRANGE;
        return error_stat;
    }


    (*mem)   = KNULL;
    uint16_t i , j;

    i = 0;
    while(i < heap->size){//pass every descriptor of the heap table
        j = 0;
        //try to found blocksCount free blocks
        while(
            (!isTaken(heap->table[j + i])) 
            && 
            (j < blocksCount)
            &&
            ((i + j) < heap->size)
        ) j++;

        if ( j == blocksCount)//if found break before i counter finish
            break;
        i++;
    }

    //if no free space found
    if ( i == heap->size){
        error_stat = ENOMEMORY;
        return error_stat;
    }

    //if memory space found set first block taken and as first
    heap->table[i] = (FIRST | BLOCK_TAKEN);
    // and set all others with the right values
    for (j = i + 1 ; j < (i + blocksCount) ; j++){
        heap->table[j-1] |= HAS_NEXT;
        heap->table[j] = BLOCK_TAKEN;
    }
    // finally set mem first level pointer to point on the first block 
    // of all blocks count
    (*mem) =(void*)((i)*HEAP_BLOCK_BYTES + ((uint32_t)heap->base));
    

    return error_stat;
}


int dallocateMem(
    HeapHandler* heap ,
    void*        mem  
){
    error_stat = KERNEL_OK;

    //check if heap size and heap Table size are relative equal
    if (heap->size != ((heap->limit+1)/HEAP_BLOCK_BYTES)){
        error_stat = ECORRUPTDATA;
        return error_stat;
    }

    // check if everything is alligned
    if (
        (!isAllign((uint32_t)heap->base)) 
        || 
        (!isAllign((uint32_t)heap->limit + 1))
        ||
        ( !isAllign((uint32_t)mem))
    ){
        error_stat = ENOTALLIGN;
        return error_stat;
    }

    


    int i = memoryToIndex(mem , heap->base);
    // is in the range of addresses , if not send the warning and do nothing
    if ( i >= heap->size ){
        error_stat = EOUTOFRANGE;
        return error_stat;
    }

    // is the specific address taken , if not do nothing
    if ( !isTaken(heap->table[i])){
        return error_stat;
    }

    // is the first (base) address if not send error
    if ( !isFirst(heap->table[i])){
        error_stat = EINVALIDARGS;
        return error_stat;
    }

    
    

    while(( i < heap->size) && ( isTaken(heap->table[i]))  ){
        if (!hasNext(heap->table[i])){
            heap->table[i] = 0;
            break;
        }

        heap->table[i] = 0;
        i++;
    }

    return error_stat;
}