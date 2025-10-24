#ifndef __FLUSHOS_IO_H__
#define __FLUSHOS_IO_H__

    #include <stdint-gcc.h>
    #include <stddef.h>

    
    extern void outb(uint8_t  data , uint16_t port);
    extern void outw(uint16_t data , uint16_t port);
    extern void outd(uint32_t data , uint16_t port);
    
    extern void inb(uint8_t * data , uint16_t port);
    extern void inw(uint16_t* data , uint16_t port);
    extern void ind(uint32_t* data , uint16_t port);

    // all of them are implemented in assembly


#endif 