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
#define print(str) text_mode_print_str((str) , TM_DARK_BLUE)
#define printc(c)  text_mode_write_char((c) , TM_DARK_BLUE)
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
struct file_stat s;
void kernel_main(void){
    disable_intt();
    pic_remap(0x20 , 0x28);

    text_mode_init(coloured_display);
    char st[] = "Hello World !!! from kernel os \n";
    print(st);
    
    
    
    interrupts_init();
    
    pic_enable_irq(1); // test keyboard interrupts :)
    
    kheap_init();
    enable_intt();
    


    disable_intt();
    struct paging_flags pflags;
    pflags.cache_disable = false;
    pflags.cache_write_through = true;
    pflags.present = true;
    pflags.user = true;
    pflags.writable = true;
    struct paging_info* pinfo =  paging_init(pflags);



    paging_switch(pinfo);

    paging_enable();
    enable_intt();


    file_system_init();
    disk_init();



    int fd = fopen("0:/Hello.txt", "r");
    if (fd > 0)
    {
        print("\nWe opened hello.txt\n");
        char read_buffer[256];
        fread(read_buffer , 5 , 1 , fd);
        print(read_buffer);
        print("\n");
        fseek(fd , 0 , SEEK_SET);
        fread(read_buffer , 5 , 1 , fd);
        print(read_buffer);
        print("\n");
        fseek(fd , -5 , SEEK_CUR);
        fread(read_buffer , 15 , 3 , fd);
        print(read_buffer);
        print("\n");
        fread(read_buffer , 15 , 3 , fd);
        print(read_buffer);
        print("\n");

        
        fstat(fd ,&s);
        print("filesize : ");
        printHex((void*)s.size);
        print("\n");
        if (s.status & FILE_STATUS_READ_ONLY){
            print("File is read only \n");
        }
        print("filename : ");
        print(s.name);

        errno res = fclose(fd);
        if (res != FLUSHOS_EGOOD){
            print("Something Wrong with fclose :( !!!\n");
        }
        res= fseek(fd , 0 , SEEK_SET);
        if (res != FLUSHOS_EGOOD){
            print("Something Wrong with fseek :( !!!\n");
        }
        res = fread(read_buffer , 5 , 1 , fd);
        if (res != FLUSHOS_EGOOD){
            print("Something Wrong with fread :( !!!\n");
        }
        print(read_buffer);
    }
    
    while(1) {}
}