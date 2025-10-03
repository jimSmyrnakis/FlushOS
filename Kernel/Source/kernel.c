#include "kernel.h"

//#include <inttypes.h> // optional, for PRI... macros if needed

// Convert a void* to a 32-bit unsigned integer (numeric value).
// Uses uintptr_t for a defined pointer -> integer conversion, then casts.
// On 32-bit targets this preserves the full pointer. On 64-bit targets the
// returned value will be truncated to 32 bits.
static uint32_t ptr_to_u32(void *p) {
    // uintptr_t is the portable integer type to hold a pointer
    uintptr_t v = (uintptr_t)p;
    return (uint32_t)v;
}

// Produce an ASCII hex string "0x1234ABCD" into user buffer.
// Requirements:
//   - buf must point to writable memory of at least 11 bytes (10 chars + NUL).
//   - The function does not use libc printf; it's safe in kernels/bootloaders.
// Returns: pointer to buf.
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

#ifndef NULL
#define NULL ((void*)0)
#endif 
int len  = 0;
void kernel_main(void){
    disable_intt();
    pic_remap(0x20 , 0x28);

    text_mode_init(coloured_display);
    char st[] = "Hello World !!! from kernel os \n";
    text_mode_print_str(st, TM_DARK_BLUE);
    
    
    
    interrupts_init();
    text_mode_print_str(" Lol" , TM_DARK_BLUE);
    enable_intt();
    pic_enable_irq(1); // test keyboard interrupts :)
    
    kheap_init();
    void* ptr1 = kmalloc(2 * 4096);
    printHex(ptr1);
    void* ptr2 = kmalloc(2 * 4096);
    printHex(ptr2);
    kfree(ptr1 + 200);

    void* ptr3 = kmalloc(2 * 4096);
    printHex(ptr3);
    kfree(ptr3 + 4095);
    void* ptr4 = kmalloc(4 * 4096);
    printHex(ptr4);
    void* ptr5 = kmalloc(4);
    printHex(ptr5);
    kfree(ptr5);
    kfree(ptr4);
    void* ptr6 = kmalloc(1);
    printHex(ptr6);

    
    




}