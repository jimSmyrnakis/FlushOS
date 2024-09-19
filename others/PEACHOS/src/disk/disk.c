#include "disk.h"
#include <io/io.h>
#include <fs/file.h>

static struct disk disk;

static int disk_read_sectors(uint32_t lba , uint8_t count , void* buffer){
    error_stat = KERNEL_OK;

    outb( 0x01F6 , ( lba >> 24 ) | 0xE0 ); // we have total 256GB addressable disk space here
    outb( 0x01F2 , (uint8_t)(count) ); // total sectors 
    outb( 0x01F3 , (uint8_t)(lba & 0x000000FF) ); 
    outb( 0x01F4 , (uint8_t)(lba >> 8) );
    outb( 0x01F5 , (uint8_t)(lba >> 16) ); 
    outb( 0x01F7 , 0x20 ); // READ COMMAND

    uint16_t* buffer16 = (uint16_t*)buffer;

    uint16_t i , j;
    // read count selectors
    for( i = 0 ; i < count ; i++){

        //check if disk is has ready our data
        uint8_t checkDisk = inb( 0x01F7 );
        while (!(checkDisk & 0x08 )) ;// waiting (polling)

        //now we are ready to read from the disk ide controller 
        for ( j = 0 ; j < 256 ; j++ ){
            buffer16[ i*count + j] = inw( 0x01F0);
        }
    }
    return error_stat;
}

void disk_search_and_init(void){
    disk.type = PEACHOS_DISK_TYPE_REAL;
    disk.sector_size = 512;
    disk.file_system = KNULL;
    disk.file_system = fs_resolve(&disk);
}

struct disk* disk_get(uint16_t index){
    if (index != 0)
        return KNULL;
    
    return &disk;
}

int disk_read_blocks(struct disk* idisk , uint32_t lba , uint8_t count , void* buffer){
    error_stat = KERNEL_OK;
    if (idisk != &disk){
        error_stat = EINVALIDARGS;
        return error_stat;
    }

    return disk_read_sectors(lba , count  , buffer);
}

