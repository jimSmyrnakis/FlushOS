#ifndef __FLUSHOS_DRIVERS_PATA_H__
#define __FLUSHOS_DRIVERS_PATA_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include "../../../../io/io.h"
    #include "../../../../errno.h"
    #include <driver/driver.h>
    #include <disk/disk.h>

    extern driver pata_driver;

    errno pata_init(void);
    errno pata_fini(void);
    errno pata_probe(void);

    enum pata_disk{
        PATA_PRIMARY_MASTER ,
        PATA_PRIMARY_SLAVE  ,
        PATA_SECONDARY_MASTER ,
        PATA_SECONDARY_SLAVE
    };
    typedef enum pata_disk pata_disk;

    struct pata_diskx {
        pata_disk _disk;
        disk_attributes _attrs;
        disk_module _module;
        bool pata_lba28; // true for lba28 , false for lba48 bits addressing 
        bool valid; // true if exists
        uint16_t ata_io;
        uint16_t ata_buss;
        uint16_t ata_drive;
        uint8_t lba28_last_high;
    };
    typedef struct pata_diskx pata_diskx;

    bool pata_detect_disks(void);

    extern pata_diskx primary_master_disk;
    extern pata_diskx primary_slave_disk;
    extern pata_diskx secondary_master_disk;
    extern pata_diskx secondary_slave_disk;

    errno pata_read_lba28(uint64_t lba, uint32_t total, void* buffer , void* priv);
    errno pata_write_lba28(uint64_t lba, uint32_t total, void* buffer , void* priv);

    errno pata_read_lba48(uint64_t lba, uint32_t total, void* buffer , void* priv);
    errno pata_write_lba48(uint64_t lba, uint32_t total, void* buffer , void* priv);

    extern pata_diskx* current_primary_drive ;
    extern pata_diskx* current_secondary_drive;

    errno pata_switch_drive(pata_diskx* pdisk , uint8_t lba27_24);

#endif 