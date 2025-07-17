#ifndef X86_32_FCALLS_H
#define X86_32_FCALLS_H

    #include "../core.h"
    #include "../error.h"
    #include "../selector/selector.h"

    struct x86_32_far_pointer{
        struct x86_32_selector selector ;
        void*                  procedure;
    };

    struct _x86_32_far_pointer{
        uint16_t         _zro;  // alligment for selector and offset
        _x86_32_selector _sel;
        uint32_t         _ofs;
    }X86_32_SYSTEM_STRUCT;

    x86_32_err_type X86_32_CALL x86_32_far_pointer_set(struct _x86_32_far_pointer* _dest , const struct x86_32_far_pointer* src);
    void            X86_32_CALL x86_32_far_pointer_get(struct x86_32_far_pointer* dest , const struct _x86_32_far_pointer* _src);

    extern void X86_32_CALL _x86_32_far_call(struct _x86_32_far_pointer* fpptr);
    

#endif 