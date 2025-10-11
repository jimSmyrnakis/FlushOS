#include "pata.h"

errno pata_read_sector(uint64_t lba, uint32_t total, void* buf)
{
    outb((lba >> 24) | 0xE0 , 0x1F6 );
    outb(total , 0x1F2 );
    outb((uint8_t)(lba & 0xff) , 0x1F3);
    outb((uint8_t)(lba >> 8) , 0x1F4);
    outb((uint8_t)(lba >> 16) , 0x1F5);
    outb(0x20 , 0x1F7);

    uint16_t* ptr = (uint16_t*) buf;
    for (int b = 0; b < total; b++)
    {
        // Wait for the buffer to be ready
        uint8_t c = 0;
        inb(&c , 0x1F7);
        while(!(c & 0x08))
        {
            inb(&c , 0x1F7);
        }

        // Copy from hard disk to memory
        for (int i = 0; i < 256; i++)
        {
            inw(ptr ,0x1F0);
            ptr++;
        }

    }
    return FLUSHOS_EGOOD;
}