#include "pata.h"
#include "pata_registers.h"
#include <print.h>
errno pata_read_lba48(uint64_t lba, uint32_t total, void* buffer , void* priv){

    return FLUSHOS_EGOOD;
}
errno pata_write_lba48(uint64_t lba, uint32_t total, void* buffer , void* priv){
    print("WRITE LBA48\n");
    return FLUSHOS_EGOOD;
}
errno pata_read_lba28(uint64_t lba, uint32_t total, void* buf , void* priv)
{
    print("READ LBA28\n");
    uint8_t status = 0;
    uint16_t* ptr = (uint16_t*)buf;
    pata_diskx* pdisk = (pata_diskx*)priv;
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;

    pata_switch_drive(pdisk , (uint8_t)((lba >> 24) & 0x0F));
    

    // Sector count
    outb((uint8_t)(total > 255 ? 0 : total) , ata_io_base + SECTOR_COUNT_REG);


    // LBA
    outb((uint8_t)lba,       ata_io_base + LBA_LOW_REGISTER);
    outb((uint8_t)(lba>>8),  ata_io_base + LBA_MID_REGISTER);
    outb((uint8_t)(lba>>16), ata_io_base + LBA_HIG_REGISTER);


    // wait to be ready for it to receive command
    do
    {
        inb(&status,ata_io_base + STATUS_REGISTER);
    }while ((status & STATUS_DRIVER_BUSY) ||
       !(status & STATUS_DRIVE_READY));  // 

    
    // READ SECTORS command
    outb(CMD_READ_LBA28_SECTORS , ata_io_base + COMMAND_REGISTER);



    for(uint32_t sector = 0; sector < total; sector++)
    {

        // Wait until data is ready
        do
        {
            inb(&status,ata_io_base + STATUS_REGISTER);
            if(status & STATUS_ERROR)
            {
                print("ATA ERROR\n");
                return FLUSHOS_EUNKNOWN;
            }

        }while((status & STATUS_DRIVER_BUSY) ||
       !(status & STATUS_PIO_READY)); // DRQ


        // Read 512 bytes = 256 words
        for(int i = 0; i < 256; i++)
        {
            inw(ptr,ata_io_base + DATA_REGISTER);
            ptr++;
        }
    }


    // Wait until device is finished
    do
    {
        inb(&status,ata_io_base + STATUS_REGISTER);

    }while ((status & STATUS_DRIVER_BUSY) ); // BSY

    return FLUSHOS_EGOOD;
}

errno pata_write_lba28(uint64_t lba, uint32_t total, void* buf , void* priv)
{
    print("WRITE LBA28\n");
    uint8_t status = 0;
    uint16_t* ptr = (uint16_t*)buf;
    pata_diskx* pdisk = (pata_diskx*)priv;
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;

    pata_switch_drive(pdisk , (uint8_t)((lba >> 24) & 0x0F));


    // Sector count
    outb((uint8_t)(total > 255 ? 0 : total) , ata_io_base + SECTOR_COUNT_REG);


    // LBA
    outb((uint8_t)lba,       ata_io_base + LBA_LOW_REGISTER);
    outb((uint8_t)(lba>>8),  ata_io_base + LBA_MID_REGISTER);
    outb((uint8_t)(lba>>16), ata_io_base + LBA_HIG_REGISTER);


    // wait to be ready for it to receive command
    do
    {
        inb(&status,ata_io_base + STATUS_REGISTER);
    }while ((status & STATUS_DRIVER_BUSY) ||
       !(status & STATUS_DRIVE_READY));  // 

    // WRITE SECTORS command
    outb(CMD_WRITE_LBA28_SECTORS , ata_io_base + COMMAND_REGISTER);



    for(uint32_t sector = 0; sector < total; sector++)
    {

        // Wait until data is ready
        do
        {
            inb(&status,ata_io_base + STATUS_REGISTER);
            if(status & STATUS_ERROR)
            {
                print("ATA ERROR\n");
                return FLUSHOS_EUNKNOWN;
            }

        }while((status & STATUS_DRIVER_BUSY) ||
       !(status & STATUS_PIO_READY)); // DRQ


        // write 512 bytes = 256 words
        for(int i = 0; i < 256; i++)
        {
            outw(*ptr,ata_io_base + DATA_REGISTER);
            ptr++;
        }
    }

    // wait to be ready for it to receive command
    do
    {
        inb(&status,ata_io_base + STATUS_REGISTER);
    }while ((status & STATUS_DRIVER_BUSY) );  // 

    outb(CMD_LBA28_FLUSH_CACHE , ata_io_base + COMMAND_REGISTER);
    // Wait until device is finished
    do
    {
        inb(&status,ata_io_base + STATUS_REGISTER);

    }while ((status & STATUS_DRIVER_BUSY)); // BSY

    return FLUSHOS_EGOOD;
}
