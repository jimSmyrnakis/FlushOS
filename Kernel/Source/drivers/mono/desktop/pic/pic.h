#ifndef __FLUSHOS_PIC_H__
#define __FLUSHOS_PIC_H__

    #include <stdint.h>
    #include <stddef.h>
    
    // port's definitions of mater-slave 8259 pic's
    #define MASTER_PIC ((uint16_t)0x0020)
    #define SLAVE_PIC  ((uint8_t) 0x00A0)
    #define MASTER_PIC_COMMAND MASTER_PIC 
    #define SLAVE_PIC_COMMAND SLAVE_PIC
    #define MASTER_PIC_DATA (MASTER_PIC + 1)
    #define SLAVE_PIC_DATA (SLAVE_PIC + 1)

    void pic_eoi(uint8_t IRQ);
    void pic_disable(void);
    void pic_remap(uint8_t vio_master , uint8_t vio_slave);
    void pic_diable_irq(uint8_t IRQline);
    void pic_enable_irq(uint8_t IRQline);

#endif 