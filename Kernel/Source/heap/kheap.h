#ifndef __FLUSHOS_KHEAP_H__
#define __FLUSHOS_KHEAP_H__

    #include <stdint.h>
    #include <stddef.h>

    void  kheap_init(void);
    void* kmalloc(size_t size);
    void* kzalloc(size_t size);
    void  kfree(void* ptr);
    

#endif 