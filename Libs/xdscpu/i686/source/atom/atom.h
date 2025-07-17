#ifndef X86_ATOM_H
#define X86_ATOM_H

    #include "../core.h"
    #include "../error.h"

    extern uint8_t  X86_32_CALL _x86_atom_exchange_8 (uint8_t * dest , uint8_t  value);
    extern uint16_t X86_32_CALL _x86_atom_exchange_16(uint16_t* dest , uint16_t value);
    extern uint32_t X86_32_CALL _x86_atom_exchange_32(uint32_t* dest , uint32_t value);
    /*  Exchanges the contents of the destination (first) and value (second) operands.
        The processor’s locking protocol is automatically implemented for the duration 
        of the exchange operation, regardless of the value of the IOPL. */
     

#endif 