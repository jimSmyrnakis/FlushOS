#include "pata.h"
#include "pata_registers.h"
#include "pata_special_cmds.h"
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
    
    uint8_t status = 0;
    uint16_t* ptr = (uint16_t*)buf;
    pata_diskx* pdisk = (pata_diskx*)priv;
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;
    errno error = FLUSHOS_EGOOD;
    pata_switch_drive(pdisk , (uint8_t)((lba >> 24) & 0x0F));


    // Sector count
    outb((uint8_t)(total > 255 ? 0 : total) , ata_io_base + SECTOR_COUNT_REG);


    // LBA
    outb((uint8_t)lba,       ata_io_base + LBA_LOW_REGISTER);
    outb((uint8_t)(lba>>8),  ata_io_base + LBA_MID_REGISTER);
    outb((uint8_t)(lba>>16), ata_io_base + LBA_HIG_REGISTER);


    // wait to be ready for it to receive command
    error = ata_wait_ready(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return ata_recover(ata_io_base , ata_ctrl_base , pdisk->ata_drive);
    }
    

    
    // READ SECTORS command
    ata_send_command( ata_io_base , ata_ctrl_base , CMD_READ_LBA28_SECTORS );
    

    for(uint32_t sector = 0; sector < total; sector++)
    {

        // Wait until data is ready
        error = ata_wait_drq(ata_io_base , ata_ctrl_base);
        if (error != FLUSHOS_EGOOD){
            pdisk->lba28_last_high = 0;
            return ata_recover(ata_io_base , ata_ctrl_base , pdisk->ata_drive);
        }



        // Read sector bytes / 2 words
        for(int i = 0; i < (pdisk->_attrs.sector_length/2); i++)
        {
            inw(ptr,ata_io_base + DATA_REGISTER);
            ptr++;
        }
    }
    ata_delay_400ns(ata_ctrl_base);


    // Wait until device is finished
    error = ata_wait_not_busy(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return ata_recover(ata_io_base , ata_ctrl_base , pdisk->ata_drive);
    }

    return FLUSHOS_EGOOD;
}

errno pata_write_lba28(uint64_t lba, uint32_t total, void* buf , void* priv)
{
    
    uint8_t status = 0;
    errno error = FLUSHOS_EGOOD;
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
    error = ata_wait_ready(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return ata_recover(ata_io_base , ata_ctrl_base , pdisk->ata_drive);
    }

    // WRITE SECTORS command
    ata_send_command(
        ata_io_base,
        ata_ctrl_base,
        CMD_WRITE_LBA28_SECTORS
    );



    for(uint32_t sector = 0; sector < total; sector++)
    {

        // Wait until data is ready
        error = ata_wait_drq(ata_io_base , ata_ctrl_base);
        if (error != FLUSHOS_EGOOD){
            pdisk->lba28_last_high = 0;
            return ata_recover(ata_io_base , ata_ctrl_base , pdisk->ata_drive);
        }


        // write sector byte / 2 words
        for(int i = 0; i < (pdisk->_attrs.sector_length/2); i++)
        {
            outw(*ptr,ata_io_base + DATA_REGISTER);
            ptr++;
        }
    }

    // wait to be ready for it to receive command
    error = ata_wait_not_busy(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return ata_recover(ata_io_base , ata_ctrl_base , pdisk->ata_drive);
    }

    outb(CMD_LBA28_FLUSH_CACHE , ata_io_base + COMMAND_REGISTER);
    // Wait until device is finished
    error = ata_wait_not_busy(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return ata_recover(ata_io_base , ata_ctrl_base , pdisk->ata_drive);
    }

    return FLUSHOS_EGOOD;
}
