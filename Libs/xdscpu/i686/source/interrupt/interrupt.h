#ifndef X86_32_INTERRUPT_H
#define X86_32_INTERRUPT_H

    #include "../core.h"
    #include "../error.h"

    extern void X86_32_CALL _x86_32_cli(void);
    /*
     *
     *
     * Description: For disable the external hardware interrupt's use this function
     * Note: This function is faster than change the eflags register via this library functionality for registers
     * 
     * 
    */
    extern void X86_32_CALL _x86_32_sti(void);
    /*
     *
     *
     * Description: For enable the external hardware interrupt's use this function
     * Note: This function is faster than change the eflags register via this library functionality for registers
     * 
     * 
    */
    extern void X86_32_CALL _x86_32_iret(void);
    /*
     *
     *
     * Description: For returnig from an interrupt procedure from this code segment , other code segment
     *              or other task (task's set tss prev task value of the interrupt task handler to the one
     *              was executed before )
     * 
     * 
    */




#endif