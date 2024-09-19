#ifndef KHEAP_H
#define KHEAP_H

#include <def.h>
#include <status.h>
#include <config.h>
#include <heap/heap.h>

void initKernelHeap(void);


void* kmalloc(uint32_t count);

void  kfree(void* ptr);

void* kzalloc(uint32_t count);



#endif 