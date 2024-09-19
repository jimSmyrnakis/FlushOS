#ifndef X86_32_IO_H
#define X86_32_IO_H

    #include "../core.h"
    #include "../error.h"

    typedef uint16_t x86_32_port;
    /* A io address is 16-bit wide in total */

    extern uint8_t  X86_32_CALL _x86_32_inb(x86_32_port port); 
    extern uint16_t X86_32_CALL _x86_32_inw(x86_32_port port);
    extern uint32_t X86_32_CALL _x86_32_ind(x86_32_port port);

    extern void X86_32_CALL _x86_32_outb(x86_32_port port , uint8_t  data);
    extern void X86_32_CALL _x86_32_outw(x86_32_port port , uint16_t data);
    extern void X86_32_CALL _x86_32_outd(x86_32_port port , uint32_t data);

    extern void X86_32_CALL _x86_32_insb(x86_32_port port , uint16_t count , uint8_t * buff);
    extern void X86_32_CALL _x86_32_insw(x86_32_port port , uint16_t count , uint16_t* buff);
    extern void X86_32_CALL _x86_32_insd(x86_32_port port , uint16_t count , uint32_t* buff);

    extern void X86_32_CALL _x86_32_outsb(x86_32_port port , uint32_t count , uint8_t * buff);
    extern void X86_32_CALL _x86_32_outsw(x86_32_port port , uint32_t count , uint16_t* buff);
    extern void X86_32_CALL _x86_32_outsd(x86_32_port port , uint32_t count , uint32_t* buff);
    


    x86_32_err_type X86_32_CALL x86_32_inb(x86_32_port port , uint8_t * data);
    x86_32_err_type X86_32_CALL x86_32_inw(x86_32_port port , uint16_t* data);
    x86_32_err_type X86_32_CALL x86_32_ind(x86_32_port port , uint32_t* data);    
    
    x86_32_err_type X86_32_CALL x86_32_outb(x86_32_port port , uint8_t  data);
    x86_32_err_type X86_32_CALL x86_32_outw(x86_32_port port , uint16_t data);
    x86_32_err_type X86_32_CALL x86_32_outd(x86_32_port port , uint32_t data);  

    x86_32_err_type X86_32_CALL x86_32_insb(x86_32_port port , uint16_t count , uint8_t * buffer);
    x86_32_err_type X86_32_CALL x86_32_insw(x86_32_port port , uint16_t count , uint16_t* buffer);
    x86_32_err_type X86_32_CALL x86_32_insd(x86_32_port port , uint16_t count , uint32_t* buffer);

    x86_32_err_type X86_32_CALL x86_32_outsb(x86_32_port port , uint16_t count , uint8_t * buffer);
    x86_32_err_type X86_32_CALL x86_32_outsw(x86_32_port port , uint16_t count , uint16_t* buffer);
    x86_32_err_type X86_32_CALL x86_32_outsd(x86_32_port port , uint16_t count , uint32_t* buffer);
    
#endif 