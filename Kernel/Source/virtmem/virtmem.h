#ifndef __FLUSHOS_VIRTMEM_H__
#define __FLUSHOS_VIRTMEM_H__

    #include "../paging/paging.h"
    #include <stdbool.h>
    #include "../errno.h"

    
    void virtmem_map(void* virt , void* phys);
#endif 