#ifndef GPSPCPU_CONFIG_H
#define GPSPCPU_CONFIG_H

    #define _XDS_X86_32_

    #ifdef _XDS_X86_32_ 
        #include <stdint.h>
        #include <stddef.h>
        #define _GPSPCPU_UI8_    uint8_t
        #define _GPSPCPU_UI16_   uint16_t 
        #define _GPSPCPU_UI32_   uint32_t 
        #define _GPSPCPU_UI64_   uint64_t
        #define _GPSPCPU_UIADDR_ uint32_t 
        #define _GPSPCPU_SYS_STR_ __attribute__((packed))
        #define _GPSPCPU_DEFS

    #endif

    #ifdef _XDS_X86_64_
        #include <stdint.h>
        #include <stddef.h>
        #define _GPSPCPU_UI8_    uint8_t
        #define _GPSPCPU_UI16_   uint16_t 
        #define _GPSPCPU_UI32_   uint32_t 
        #define _GPSPCPU_UI64_   uint64_t
        #define _GPSPCPU_UIADDR_ uint64_t 

        #define _GPSPCPU_DEFS
    #endif

    #ifndef _GPSPCPU_DEFS
        just node "Missing basic definitions ==> compiler must be able for 64,32,16 and 8 bit numeric operations "
    #endif

    typedef _GPSPCPU_UI64_      GPSPCPU_u64b;
    typedef _GPSPCPU_UI32_      GPSPCPU_u32b;
    typedef _GPSPCPU_UI16_      GPSPCPU_u16b;
    typedef _GPSPCPU_UI8_       GPSPCPU_u8b ;
    typedef _GPSPCPU_UIADDR_    GPSPCPU_addr;


#endif