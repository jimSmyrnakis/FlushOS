#ifndef __FLUSHOS_IDT_H__
#define __FLUSHOS_IDT_H__

    #include <stdint-gcc.h>
    #include <stddef.h>
    #include "../errno.h"


    // struct of interrupt descriptor based on x86-32 protected mode 
    typedef struct {
        uint16_t offset_lo16 ;
        uint16_t selector    ;
        uint8_t  zero        ;
        uint8_t  attributes  ; // type of interrupt decriptor and attributes
        uint16_t offset_hi16 ;

    } __attribute__((packed)) interrupt_descriptor; 

    // struct of where the idt is on memory and the size in bytes of it (limit = size - 1)
    // based on x86-32 protected mode
    typedef struct {
        uint16_t limit;
        uint32_t base ;
    } __attribute__((packed)) idtr;

    // Types of interrupt descriptors
    #define INTTYPE_INTT_GATE       ((uint8_t) 0x0E)
    #define INTTYPE_TRAP_GATE       ((uint8_t) 0x0F)
    #define INTTYPE_TASK_GATE       ((uint8_t) 0x05)
    #define INTATTR_PRESENT         ((uint8_t) 0x80)
    #define INTATTR_SUPERVISOR      ((uint8_t) 0x00)
    #define INTATTR_USER            ((uint8_t) 0x60)
    #define INTATTR_S               ((uint8_t) 0x10)

    uint16_t get_max_interrupt_descriptors(void);

    void idt_init(
        interrupt_descriptor*  idt ,
        uint16_t               idt_count ,
        idtr*                  ptr 
    );

    void idt_set_intt_gate(
        interrupt_descriptor* intt    ,
        uint16_t              intt_no ,
        void*                 proc 
    );



    // send's the new idt base + limit attributes 
    extern void idtr_load(idtr* ptr);
    // receive's the current idt base + limit attributes
    extern void idtr_store(idtr* ptr);
    // enable maskable interrupts
    extern void enable_intt(void);
    // disables makable interrupts
    extern void disable_intt(void);


#endif 