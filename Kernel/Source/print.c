#include "print.h"

static uint32_t ptr_to_u32(void *p) {
    // uintptr_t is the portable integer type to hold a pointer
    uintptr_t v = (uintptr_t)p;
    return (uint32_t)v;
}


static char * ptr_to_hex_str(void *p, char *buf, size_t buflen) {
    // need 10 chars + NUL
    if (!buf || buflen < 11) {
        if (buf && buflen > 0) buf[0] = '\0';
        return buf;
    }

    uint32_t v = ptr_to_u32(p);

    const char hex[] = "0123456789ABCDEF";

    buf[0] = '0';
    buf[1] = 'x';
    // write 8 hex digits (big-endian style)
    for (int i = 0; i < 8; ++i) {
        // most-significant nibble first
        int shift = (7 - i) * 4;
        uint8_t nibble = (v >> shift) & 0xF;
        buf[2 + i] = hex[nibble];
    }
    buf[10] = '\0';
    return buf;
}


void printHex(void* ptr){
    char buf[1024];
    ptr_to_hex_str(ptr , buf , 1024);
    text_mode_print_str("\n" , TM_DARK_BLUE);
    text_mode_print_str(buf , TM_DARK_BLUE);
    text_mode_print_str("\n" , TM_DARK_BLUE);
}