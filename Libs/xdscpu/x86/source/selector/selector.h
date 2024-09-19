#ifndef X86_32_SELECTOR_H
#define X86_32_SELECTOR_H

    #include "../core.h"
    #include "../error.h"

    typedef uint16_t _x86_32_selector;

    struct x86_32_selector{
        uint16_t       index;
        enum x86_32_pl rpl  ;
        bool           ti   ;
    };

    x86_32_err_type X86_32_CALL x86_32_selector_set(_x86_32_selector* dest , const struct x86_32_selector* src);
    void            X86_32_CALL x86_32_selector_get(struct x86_32_selector* dest , const _x86_32_selector* src);




#endif 