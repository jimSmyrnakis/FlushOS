#ifndef X86_32_TSS_H
#define X86_32_TSS_H

    #include "../core.h"
    #include "../error.h"

    struct _x86_32_tss32{
        uint32_t prevtss;   // Previus tss task link
        uint32_t esp0   ;   // stack pointer for privilige 0
        uint32_t ss0    ;   // stack data segment for privilige 0
        uint32_t esp1   ;   // stack pointer for privilige 1
        uint32_t ss1    ;   // stack data segment for privilige 1
        uint32_t esp2   ;   // stack pointer for privilige 2
        uint32_t ss2    ;   // stack data segment for privilige 2
        uint32_t cr3    ;   // physical address for paging directory table
        uint32_t eip    ;   // last instrunction pointer value from last task switch 
        uint32_t eflags ;   // eflags register image from last task switch
        uint32_t eax    ;   // gpr's
        uint32_t ecx    ;   // ...
        uint32_t edx    ;   // ...
        uint32_t ebx    ;   // ...
        uint32_t esp    ;   // currently stack pointer
        uint32_t ebp    ;   // base stack pointer (used for the callee function to save the esp )
        uint32_t esi    ;   // gpr plus source register for string function's and specific machine commands
        uint32_t edi    ;   // gpr plus destination register for string function's and specific machine commands
        uint32_t es     ;   // extra data segment 1 (value is a selector)
        uint32_t cs     ;   // code segment (value is a selector)
        uint32_t ss     ;   // stack segment (must be a writable data segment , value is a selector)
        uint32_t ds     ;   // data segment (value is a selector)
        uint32_t fs     ;   // extra data segment 2 (value is a selector)
        uint32_t gs     ;   // extra data segment 3 (value is a selector)
        uint32_t ldt    ;   // local descriptor table (value is a selector)
        uint16_t t      ;   // T flag bit is enable for a task debug exception to generate 
        uint16_t iobaddr;   // io map structure base address 

    }X86_32_SYSTEM_STRUCT;

    

#endif 