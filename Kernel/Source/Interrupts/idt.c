#include "idt.h"
#include "../std/memory.h"
#include "../config.h"

#define MAX_INTERRUPTS_COUNT 256

uint16_t get_max_interrupt_descriptors(void){
    return MAX_INTERRUPTS_COUNT;
}

void idt_init(
    interrupt_descriptor*  idt ,
    uint16_t               idt_count ,
    idtr*                  ptr 
){

    memset(idt , 0 , idt_count * sizeof(interrupt_descriptor));
    ptr->base = (uint32_t)idt;
    ptr->limit = (idt_count * sizeof(interrupt_descriptor)) - 1;
}

void idt_set_intt_gate(
    interrupt_descriptor* idt    ,
    uint16_t              intt_no ,
    void*                 proc 
){
    interrupt_descriptor* intt = &idt[intt_no];
    uint32_t proc32 = (uint32_t)proc;
    intt->zero = 0;
    intt->attributes = INTTYPE_INTT_GATE | INTATTR_PRESENT | INTATTR_SUPERVISOR ;
    intt->offset_lo16 = proc32 & 0x0000FFFF;
    intt->offset_hi16 = ((proc32 & 0xFFFF0000) >> 16);
    intt->selector = KERNEL_CODE_SELECTOR;
    
}
