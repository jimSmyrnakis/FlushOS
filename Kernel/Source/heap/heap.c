#include "heap.h"
#include "../std/memory.h"

// algorithm will be the most basic for moment
#define HAS_NEXT        ((uint8_t)0x80)
#define IS_FIRST        ((uint8_t)0x40)
#define SYSTEM_BLOCK    ((uint8_t)0x20)
#define ET3             ((uint8_t)0x08)
#define ET2             ((uint8_t)0x04)
#define ET1             ((uint8_t)0x02)
#define BLOCK_TAKEN     ((uint8_t)0x01)

#ifndef NULL
#define NULL ((void*)0)
#endif 

#define FLUSHOS_EBADSIZE 10
#define FLUSHOS_EBADBLCKSIZE 11

uiptr align_up(uiptr base , uint16_t align){
    uiptr res = base ;
    uiptr offset = base % align;
    if (offset != 0)
        res += align - (base % align);

    return res;
}

errno heap_create(struct heap_attr attr , struct heap** heap){
    struct heap * newHeap = NULL;
    (*heap) = NULL;

    uiptr base = attr.base;
    uiptr size = attr.size;
    uint16_t block_size = attr.block_size;
    if (block_size < 128)
        return FLUSHOS_EBADBLCKSIZE;
    
    uint16_t desire_block_count = size / block_size;
    if (desire_block_count <= 1)
        return FLUSHOS_EBADSIZE;
    

    //now we have the desire space e have to find the right alligned address for each 
    //struct , so the code be compatible with cpus that may required alligment (x86 is 
    //not required it but still is a good practice )

    uiptr heap_struct_base = align_up(base , sizeof(struct heap));
    uiptr info_struct_base = align_up(
        heap_struct_base + sizeof(struct heap),
        sizeof(struct heap_info));

    uiptr heap_table_base = info_struct_base + sizeof(struct heap_info);
    uint16_t heap_table_size = desire_block_count ;
    // our heap table will include these system blocks as HAS_ALLOCATED and SYSTEM_BLOCK
    // this way we know that these are not used for another purpose :)
    uiptr user_heap_base = align_up(heap_table_base + heap_table_size , block_size);
    
    //Now we start set up our structs :)
    newHeap = (struct heap*)heap_struct_base;
    newHeap->info = (struct heap_info*)info_struct_base;
    newHeap->sys_data = (void*)heap_table_base;
    newHeap->info->base = base;
    newHeap->info->size = size;
    newHeap->info->blck_size = block_size;
    newHeap->info->heap_base = user_heap_base;
    newHeap->info->heap_size = size - (user_heap_base - base );
    newHeap->info->syst_base = base;
    newHeap->info->syst_size = user_heap_base - base ;
    newHeap->info->avai_blks = newHeap->info->heap_size / block_size;
    
    uint8_t system_entities = SYSTEM_BLOCK ;
    uint8_t user_new_entities = 0;
    uint16_t system_blocks = desire_block_count - newHeap->info->avai_blks;
// sys data is void* and my memset is memset(void* , int , size_t)
    memset(newHeap->sys_data , system_entities , system_blocks);
    memset(newHeap->sys_data + system_blocks , user_new_entities ,newHeap->info->avai_blks);  )
    

    
    (*heap) = newHeap;
    return FLUSHOS_EGOOD;
}

struct heap_info heap_get_info(struct heap* id){
    return *(id->info);
}
bool isBlockFree(uint8_t entry){
    return !(entry & BLOCK_TAKEN) && !(entry & SYSTEM_BLOCK);
}


void* heap_malloc(struct heap* id , size_t size){
    if (size == 0)
        return NULL;

    uint8_t* table = id->sys_data;
    uint16_t count = id->info->size / id->info->blck_size;
    uint16_t blocks_asked = size / id->info->blck_size;
    uint16_t i = 0;
    uiptr ptr = 0;
    while( i < count){
        
        // search the first available block 
        if (isBlockFree(table[i]) && ((i + blocks_asked) < count))
        {
            bool isFounded = true;
            // search to find blocks_asked available blocks
            for (uint16_t j = i ; j < (i+blocks_asked) ; j++){
                if (!isBlockFree(table[j]))
                {
                    isFounded = false;
                    break;
                }
            }
            // if not found then search for the next available series of blocks
            if (!isFounded){
                i += blocks_asked;
                continue;
            }
                
            // else allocate all elements :)
            for (uint16_t j = i ; j < (i+blocks_asked) ; j++){
                uint8_t block = BLOCK_TAKEN;
                if (i == j)
                    block |= IS_FIRST;
                if ((j + 1) < (i + blocks_asked) )
                    block |= HAS_NEXT;

                table[j] = block;
            }

            //ptr = id->info->heap_base + (i - id->info-> * id->info->blck_size ;
            break;
        }

        i++;
    }

}

void* heap_zalloc(struct heap* id , size_t size){
    
}

bool  heap_free(struct heap* id , void* ptr){

}