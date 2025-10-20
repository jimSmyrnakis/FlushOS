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
void kernel_main(void){
    disable_intt();
    pic_remap(0x20 , 0x28);

    text_mode_init(coloured_display);
    char st[] = "Hello World !!! from kernel os \n";
    print(st);
    
    
    
    interrupts_init();
    print(" Lol");
    
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


    char* ptr = (char*)kmalloc(1);
    char* vptr  = (char*)0x1000;
    char* vptr2 = (char*)0x2000;

    struct page_info for_ptr;
    for_ptr.phyical_addr = ptr;
    for_ptr.flags = pflags;

    paging_switch(pinfo);
    paging_set(pinfo , vptr , &for_ptr);
    virtmem_map(vptr2 , ptr);

    paging_enable();
    enable_intt();

    vptr[0] = 'H';
    vptr[1] = 'e';
    vptr2[2] = 'l';
    ptr[3] = 'l';
    ptr[4] = '0';
    vptr2[5] = '\n';

    print(ptr);
    print(vptr);
    print(vptr2);

    file_system_init();
    disk_init();
    char buffer[512];
    disk_read_sector(disk_get(0) ,  0 , 1 , buffer);
    char buffer2[18];
    strncpy(buffer2 , buffer , 18);
    print(&buffer2[3]);

    const char path[256] = "0:/path1/path3.txt";
    struct path_root* paths = path_parser_parse(path , NULL);

    void* ptr5 = kmalloc(1);
    printHex(ptr5);
    print("\n");
    printc((char)paths->disk_no + '0');
    print(":/");
    struct path_part* part = paths->first;

    while (part)
    {
        print("\n");
        print(part->part);
        part = part->next;
    }

    path_parser_free_parts(paths);
    print("\n");
    void* ptr6 = kmalloc(1);
    printHex(ptr6);
    char test_stream_buffer[1024] = {0};
    struct disk_stream* stream = disk_stream_create(DISK_TYPE_PATA_PRIMARY);
    disk_stream_seek(stream , SEEK_SET , 3);
    disk_stream_read(stream , test_stream_buffer , 1024);
    print(test_stream_buffer);
    disk_stream_destroy(stream);


    errno fd = fopen("0:/Hello.txt", "r");
    if (fd == FLUSHOS_EGOOD)
    {
        print("We opened hello.txt\n");
    }
    while(1) {}
}