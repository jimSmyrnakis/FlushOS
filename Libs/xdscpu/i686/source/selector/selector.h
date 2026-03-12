#ifndef X86_32_SELECTOR_H
#define X86_32_SELECTOR_H

    #include "../core.h"
    #include "../error.h"

    /**
     * @author Dimitris Smyrnakis
     * @brief The system struct of a selector that can be loaded to cs,es,ds,gs,fs,ss 
     * segment selector register's of the cpu 
     */
    typedef uint16_t _x86_32_selector;

    /**
     * @author Dimitris Smyrnakis
     * @brief A more human readable selector version for easier usage of it .
     * 
     */
    struct x86_32_selector{
        uint16_t       index; /* The index in bytes offset for the */
        enum x86_32_pl rpl  ;
        bool           ti   ;
    };

    x86_32_err_type X86_32_CALL x86_32_selector_set(_x86_32_selector* dest , const struct x86_32_selector* src);
    void            X86_32_CALL x86_32_selector_get(struct x86_32_selector* dest , const _x86_32_selector* src);




#endif 