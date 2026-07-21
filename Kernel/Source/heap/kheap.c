#include "kheap.h"
#include "heap.h"

static struct heap* hid ;

#ifndef NULL
#define NULL ((void*)0)
#endif 
void  kheap_init(void){
    struct heap_attr attrs;
    attrs.base = 0x04000000;
    attrs.block_size = 4096;
    attrs.size = 100 * 1024 * 1024;// 100 MB
    hid = NULL;
    errno res = heap_create(attrs , &hid);
    
    
}

void* kmalloc(size_t size){
    return heap_malloc(hid , size);
}

void* kzalloc(size_t size){
    return heap_zalloc(hid , size);
}

void  kfree(void* ptr){
    heap_free(hid , ptr);
}