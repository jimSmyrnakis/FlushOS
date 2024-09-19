#ifndef X86_32_CR2
#define X86_32_CR2

    #include "../../core.h"
    #include "../../error.h"

    struct _x86_32_cr2{
        uint32_t lfaddr;
    }X86_32_SYSTEM_STRUCT;

    extern void X86_32_CALL _x86_32_cr2_write(const struct _x86_32_cr2* reg_value);
    extern void X86_32_CALL _x86_32_cr2_read (const struct _x86_32_cr2* reg_value);

#endif 