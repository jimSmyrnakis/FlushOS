#include "pic.h"

#include "../../../../io/io.h"
// commands of pic 
#define PIC_EOI 0x20


void pic_eoi(uint8_t IRQ){
    if (IRQ >= 8) // if interrupt came from slave pic , send him too eoi
        outb( PIC_EOI , SLAVE_PIC_COMMAND);
    
    outb(PIC_EOI , MASTER_PIC_COMMAND);
}

void pic_disable(void){
    outb(0xFF , MASTER_PIC_DATA);
    outb(0xFF , SLAVE_PIC_DATA );

}

// initiallization special word bits set up
#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_INIT	0x10		/* Initialization - required! */
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define CASCADE_IRQ 2
void io_wait(void){
    outb(0x00, 0x80);
}
void pic_remap(uint8_t vio_master , uint8_t vio_slave){
    outb(ICW1_INIT | ICW1_ICW4 , MASTER_PIC_COMMAND);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(ICW1_INIT | ICW1_ICW4 , SLAVE_PIC_COMMAND);
	io_wait();
	outb( vio_master, MASTER_PIC_DATA);                // ICW2: Master PIC vector offset
	io_wait();
	outb( vio_slave ,SLAVE_PIC_DATA );                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(1 << CASCADE_IRQ , MASTER_PIC_DATA);          // ICW3: tell Master PIC that there is a slave PIC at IRQ2
	io_wait();
	outb(2,  SLAVE_PIC_DATA);                          // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
	
	outb( ICW4_8086, MASTER_PIC_DATA );                // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb( ICW4_8086, SLAVE_PIC_DATA );
	io_wait();

	// Unmask both PICs.
	//outb(0 , MASTER_PIC_DATA );
	//outb(0 , SLAVE_PIC_DATA  );
    pic_disable();
}

void pic_disable_irq(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = MASTER_PIC_DATA;
    } else {
        port = SLAVE_PIC_DATA;
        IRQline -= 8;
    }
    uint8_t irqs = 0;
    inb(&irqs , port);
    value = irqs | (1 << IRQline);
    outb(value,port );        
}

void pic_enable_irq(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = MASTER_PIC_DATA;
    } else {
        port = SLAVE_PIC_DATA;
        IRQline -= 8;
    }
    uint8_t irqs = 0;
    inb(&irqs , port);
    value = irqs & ~(1 << IRQline);
    outb(value,port );        
}