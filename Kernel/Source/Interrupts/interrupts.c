#include "interrupts.h"

interrupt_descriptor idt[256];
idtr idtref;

#include "../drivers/mono/desktop/text_mode/text_mode.h"
#include "../drivers/mono/desktop/pic/pic.h"
void default_handler(void){
    text_mode_print_str("Divide with zero :P !!!" , TM_DARK_BLUE);
}

void default_irq_handler(void){
    text_mode_print_str("Device interrupt !!!" , TM_DARK_BLUE);
    
    pic_eoi(0x01);
}

extern void isr_default(void);
extern void isr_irq_default(void);
void interrupts_init() {
    idt_init(idt , 256 , &idtref);

    for (int i = 0; i < 256; i++) {
        if ((i > 31) && (i <= (31 + 16))){
            set_interrupt(isr_irq_default , i);
        }
        else 
            set_interrupt(isr_default, i);
    }

    

    idtr_load(&idtref);
}

void set_interrupt(void* proc , uint16_t intno){
    idt_set_intt_gate(idt , intno , proc);
}