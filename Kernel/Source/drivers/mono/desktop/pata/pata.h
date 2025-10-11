#ifndef __FLUSHOS_DRIVERS_PATA_H__
#define __FLUSHOS_DRIVERS_PATA_H__

    #include <stdint.h>
    #include <stddef.h>
    #include "../../../../io/io.h"
    #include "../../../../errno.h"

    errno pata_read_sector(uint64_t lba, uint32_t total, void* buf);
    // even tho the 64 bit size is too big still is for abstraction layer of the disk 
    
#endif 