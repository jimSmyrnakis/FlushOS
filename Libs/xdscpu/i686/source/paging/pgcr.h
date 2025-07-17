#ifndef X86_32_PTLBU_H
#define X86_32_PTLBU_H

    #include "../core.h"
    #include "../error.h"
    #include "../registers/control/control.h"
    #include "pgdr.h"

    void X86_32_CALL x86_32_paging_cache_reload(void);
    /*
     *
     *
     * A general way to update page caching tlb , is not the best as this
     * library use this processor in more generic way and force's the cache
     * to clean all the entries and not a specific tlb entry .  
     * 
     * 
    */

#endif 