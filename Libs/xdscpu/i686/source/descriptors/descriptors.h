#ifndef X86_32_DESCRIPTOR_H
#define X86_32_DESCRIPTOR_H

    #define X86_32_DESCRIPTOR_ALLIGNED_PERFOMANCE 16
    #define X86_32_SIZE_OF_DESCRIPTOR (sizeof(struct _x86_32_descriptor))
    #include "../core.h"
    #include "../error.h"
    #include "../selector/selector.h"

    struct _x86_32_descriptor{
        uint32_t dword1;
        uint32_t dword2;
    } X86_32_SYSTEM_STRUCT;

    void            X86_32_CALL  x86_32_descriptor_init(struct _x86_32_descriptor* desc);

    x86_32_err_type X86_32_CALL x86_32_descriptor_set_limit(struct _x86_32_descriptor* desc , uint32_t new_limit , uint32_t* old_limit);
    void            X86_32_CALL x86_32_descriptor_get_limit(const struct _x86_32_descriptor* desc , uint32_t* limit);

    void            X86_32_CALL x86_32_descriptor_set_base (struct _x86_32_descriptor* desc , uint32_t new_base  , uint32_t* old_base );
    void            X86_32_CALL x86_32_descriptor_get_base (const struct _x86_32_descriptor* desc , uint32_t* base );

    void            X86_32_CALL x86_32_descriptor_set_present(struct _x86_32_descriptor* desc , bool  present);
    void            X86_32_CALL x86_32_descriptor_get_present(const struct _x86_32_descriptor* desc , bool* present);

    void            X86_32_CALL x86_32_descriptor_set_accessed(struct _x86_32_descriptor* desc , bool  accessed);
    void            X86_32_CALL x86_32_descriptor_get_accessed(const struct _x86_32_descriptor* desc , bool* accessed);

    void            X86_32_CALL x86_32_descriptor_set_supervisor(struct _x86_32_descriptor* desc , bool supervisor );
    void            X86_32_CALL x86_32_descriptor_get_supervisor(const struct _x86_32_descriptor* desc , bool* supervisor);

    void            X86_32_CALL x86_32_descriptor_set_selector(struct _x86_32_descriptor* dest , const _x86_32_selector* src);
    void            X86_32_CALL x86_32_descriptor_get_selector(_x86_32_selector* dest , const struct _x86_32_descriptor* src);

    void            X86_32_CALL x86_32_descriptor_set_dpl(struct _x86_32_descriptor* dest , const enum x86_32_pl* src);
    void            X86_32_CALL x86_32_descriptor_get_dpl(enum x86_32_pl* dest , const struct _x86_32_descriptor* src);

    void            X86_32_CALL x86_32_descriptor_set_offset(struct _x86_32_descriptor* dest , const uint32_t* src);
    void            X86_32_CALL x86_32_descriptor_get_offset(uint32_t* dest , const struct _x86_32_descriptor* src);

    void            X86_32_CALL x86_32_descriptor_set_null(struct _x86_32_descriptor* desc);

#endif
