#ifndef X86_32_PGDR
#define X86_32_PGDR

    #include "../core.h"
    #include "../error.h"
    #include "../registers/control/control.h"

    struct x86_32_pdir{

        uint32_t addr;
        bool     caching;
        bool     write_through;

    };

    x86_32_err_type X86_32_CALL x86_32_pdir_set(const struct x86_32_pdir* pd);
    void            X86_32_CALL x86_32_pdir_get(struct x86_32_pdir* pd);
    void            X86_32_CALL x86_32_enable_paging (void);
    void            X86_32_CALL x86_32_disable_paging(void);

#endif 