#ifndef X86_32_CORE_H
#define X86_32_CORE_H

    #include <stdint.h>
    #include <stddef.h>

    #define X86_32_CALL __attribute__((cdecl))
    #define X86_32_SYSTEM_STRUCT __attribute__((packed))
    #define X86_32_ADDRESABLE_SPACE ((uint32_t) 0xFFFFFFFF)
    #define X86_32_NULL     ((void*) 0)
    #define X86_32_SET_BIT(type , pos) (((type)1) << (pos))

    #define x86_32_fast_get( src , BIT_FLAG , dest_field ) (dest_field) = (((*(src)) & BIT_FLAG) ? true : false )
    #define x86_32_fast_set( cond ,  dest_ptr , defined_val ) ( (*(dest_ptr)) =  ( (cond) ? ( (*(dest_ptr)) | (defined_val) ) : ( (*(dest_ptr)) & ~(defined_val) ) ) )
    #define x86_32_swap(type , arg0 , arg1) {type temp = arg0; arg0 = arg1; arg1 = temp;}

    enum x86_32_pl{
        x86_32_pl_0 ,
        x86_32_pl_1 ,
        x86_32_pl_2 ,
        x86_32_pl_3
    };

    typedef uint16_t bool;

    #define true  ((bool)1)
    #define false ((bool)0)

    #define x86_32_user_mode        ((enum x86_32_pl) x86_32_pl_3)
    #define x86_32_supervisor_mode  ((enum x86_32_pl) x86_32_pl_0)

#endif 