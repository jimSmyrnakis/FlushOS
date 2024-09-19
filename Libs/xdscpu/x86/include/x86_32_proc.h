#ifndef X86_32_PROC_H
#define X86_32_PROC_H


    #include "../source/core.h"
    #include "../source/error.h"

    // all descriptors
    #include "../source/descriptors/descriptors.h"
    #include "../source/descriptors/segment/segment.h"
    #include "../source/descriptors/segment/code.h"
    #include "../source/descriptors/segment/data.h"
    #include "../source/descriptors/system/system.h"
    #include "../source/descriptors/system/call_gate32.h"
    #include "../source/descriptors/system/intt_gate32.h"
    #include "../source/descriptors/system/task_gate32.h"
    #include "../source/descriptors/system/trap_gate32.h"
    #include "../source/descriptors/system/tss32d.h"
    #include "../source/descriptors/system/ldtd.h"

    //selector
    #include "../source/selector/selector.h"

    //paging 4KB 
    #include "../source/paging/pde.h"
    #include "../source/paging/pte.h"
    #include "../source/paging/pgcr.h"
    #include "../source/paging/pgdr.h"
    
    //task
    #include "../source/task/tss32.h"

    //registers
    #include "../source/registers/control/control.h"
    #include "../source/registers/eflags/eflags.h"
    #include "../source/registers/debug/debug.h"
    #include "../source/registers/segment/segment.h"
    #include "../source/registers/system/system.h"

    //descriptor tables
    #include "../source/dtables/dtables.h"
    #include "../source/dtables/gdt/gdt.h"
    #include "../source/dtables/idt/idt.h"
    #include "../source/dtables/ldt/ldt.h"

    //exception code (ecode)
    #include "../source/ecode/ecode.h"

    // far calls
    #include "../source/farcalls/farcalls.h"

    //input/output commands
    #include "../source/io/io.h"

    //give's interrupt basic functionality
    #include "../source/interrupt/interrupt.h"
    
#endif 