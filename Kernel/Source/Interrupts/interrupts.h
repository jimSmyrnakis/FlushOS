#ifndef __FLUSHOS_INTERRUPTS_H__
#define __FLUSHOS_INTERRUPTS_H__

    #include "idt.h"

    void interrupts_init();

    void set_interrupt(void* proc , uint16_t intno);
    void default_handler(void);
#endif 