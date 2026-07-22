#include "pata.h"
#include "pata_registers.h"
#include "pata_special_cmds.h"
#include <print.h>

errno pata_read_lba48(uint64_t lba, uint32_t total, void* buf , void* priv)
{
    // this should never called wrong from the up layer
    if (total > 0xFFFF) total = 0;

    uint8_t status = 0;
    uint16_t* ptr = (uint16_t*)buf;
    pata_diskx* pdisk = (pata_diskx*)priv;
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;
    errno error = FLUSHOS_EGOOD;
    error = pata_switch_drive(pdisk , 0);
    if (error != FLUSHOS_EGOOD)
        return error;

    // high bytes first

    outb((total >> 8) & 0xFF,
        ata_io_base + SECTOR_COUNT_REG);

    outb((lba >> 24) & 0xFF,
        ata_io_base + LBA_LOW_REGISTER);

    outb((lba >> 32) & 0xFF,
        ata_io_base + LBA_MID_REGISTER);

    outb((lba >> 40) & 0xFF,
        ata_io_base + LBA_HIG_REGISTER);


    // low bytes

    outb(total & 0xFF,
        ata_io_base + SECTOR_COUNT_REG);

    outb(lba & 0xFF,
        ata_io_base + LBA_LOW_REGISTER);

    outb((lba >> 8) & 0xFF,
        ata_io_base + LBA_MID_REGISTER);

    outb((lba >> 16) & 0xFF,
        ata_io_base + LBA_HIG_REGISTER);


    // wait to be ready for it to receive command
    error = ata_wait_ready(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return pata_handle_error(pdisk , error);
    }
    

    
    // READ SECTORS command
    ata_send_command( ata_io_base , ata_ctrl_base , CMD_READ_LBA48_SECTORS );
    
    uint32_t total2 = (total) ? total : 0x10000;
    for(uint32_t sector = 0; sector < total2; sector++)
    {

        // Wait until data is ready
        error = ata_wait_drq(ata_io_base , ata_ctrl_base);
        if (error != FLUSHOS_EGOOD){
            pdisk->lba28_last_high = 0;
            return pata_handle_error(pdisk , error);
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
        return pata_handle_error(pdisk , error);
    }

    return FLUSHOS_EGOOD;
}

errno pata_write_lba48(uint64_t lba, uint32_t total, void* buf , void* priv)
{
    // this should never called wrong from the up layer
    if (total > 0xFFFF) total = 0;
    uint8_t status = 0;
    errno error = FLUSHOS_EGOOD;
    uint16_t* ptr = (uint16_t*)buf;
    pata_diskx* pdisk = (pata_diskx*)priv;
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;
    error = pata_switch_drive(pdisk , 0);
    if (error != FLUSHOS_EGOOD)
        return error;


    // high bytes first

    outb((total >> 8) & 0xFF,
        ata_io_base + SECTOR_COUNT_REG);

    outb((lba >> 24) & 0xFF,
        ata_io_base + LBA_LOW_REGISTER);

    outb((lba >> 32) & 0xFF,
        ata_io_base + LBA_MID_REGISTER);

    outb((lba >> 40) & 0xFF,
        ata_io_base + LBA_HIG_REGISTER);


    // low bytes

    outb(total & 0xFF,
        ata_io_base + SECTOR_COUNT_REG);

    outb(lba & 0xFF,
        ata_io_base + LBA_LOW_REGISTER);

    outb((lba >> 8) & 0xFF,
        ata_io_base + LBA_MID_REGISTER);

    outb((lba >> 16) & 0xFF,
        ata_io_base + LBA_HIG_REGISTER);


    // wait to be ready for it to receive command
    error = ata_wait_ready(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return pata_handle_error(pdisk , error);
    }

    // WRITE SECTORS command
    ata_send_command(
        ata_io_base,
        ata_ctrl_base,
        CMD_WRITE_LBA48_SECTORS
    );


    uint32_t total2 = (total) ? total : 0x10000;
    for(uint32_t sector = 0; sector < total2; sector++)
    {

        // Wait until data is ready
        error = ata_wait_drq(ata_io_base , ata_ctrl_base);
        if (error != FLUSHOS_EGOOD){
            pdisk->lba28_last_high = 0;
            return pata_handle_error(pdisk , error);
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
        return pata_handle_error(pdisk , error);
    }

    ata_send_command(ata_io_base , ata_ctrl_base ,CMD_LBA48_FLUSH_CACHE );
    // Wait until device is finished
    error = ata_wait_not_busy(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return pata_handle_error(pdisk , error);
    }

    return FLUSHOS_EGOOD;
}






errno pata_read_lba28(uint64_t lba, uint32_t total, void* buf , void* priv)
{
    // this should never called wrong from the up layer
    if (total > 0xFF) total = 0;
    uint8_t status = 0;
    uint16_t* ptr = (uint16_t*)buf;
    pata_diskx* pdisk = (pata_diskx*)priv;
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;
    errno error = FLUSHOS_EGOOD;
    error = pata_switch_drive(pdisk , (uint8_t)((lba >> 24) & 0x0F));
    if (error != FLUSHOS_EGOOD) return error;

    // Sector count
    outb((uint8_t)(total) , ata_io_base + SECTOR_COUNT_REG);


    // LBA
    outb((uint8_t)lba,       ata_io_base + LBA_LOW_REGISTER);
    outb((uint8_t)(lba>>8),  ata_io_base + LBA_MID_REGISTER);
    outb((uint8_t)(lba>>16), ata_io_base + LBA_HIG_REGISTER);


    // wait to be ready for it to receive command
    error = ata_wait_ready(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return pata_handle_error(pdisk , error);
    }
    

    
    // READ SECTORS command
    ata_send_command( ata_io_base , ata_ctrl_base , CMD_READ_LBA28_SECTORS );
    
    uint32_t total2 = (total) ? total : 0x100;
    for(uint32_t sector = 0; sector < total2; sector++)
    {

        // Wait until data is ready
        error = ata_wait_drq(ata_io_base , ata_ctrl_base);
        if (error != FLUSHOS_EGOOD){
            pdisk->lba28_last_high = 0;
            return pata_handle_error(pdisk , error);
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
        return pata_handle_error(pdisk , error);
    }

    return FLUSHOS_EGOOD;
}

errno pata_write_lba28(uint64_t lba, uint32_t total, void* buf , void* priv)
{
    if (total > 0xFF) total = 0;

    uint8_t status = 0;
    errno error = FLUSHOS_EGOOD;
    uint16_t* ptr = (uint16_t*)buf;
    pata_diskx* pdisk = (pata_diskx*)priv;
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;

    error = pata_switch_drive(pdisk , (uint8_t)((lba >> 24) & 0x0F));
    if (error != FLUSHOS_EGOOD) return error;

    // Sector count
    outb((uint8_t)(total) , ata_io_base + SECTOR_COUNT_REG);


    // LBA
    outb((uint8_t)lba,       ata_io_base + LBA_LOW_REGISTER);
    outb((uint8_t)(lba>>8),  ata_io_base + LBA_MID_REGISTER);
    outb((uint8_t)(lba>>16), ata_io_base + LBA_HIG_REGISTER);


    // wait to be ready for it to receive command
    error = ata_wait_ready(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return pata_handle_error(pdisk , error);
    }

    // WRITE SECTORS command
    ata_send_command(
        ata_io_base,
        ata_ctrl_base,
        CMD_WRITE_LBA28_SECTORS
    );


    uint32_t total2 = (total) ? total : 0x100;
    for(uint32_t sector = 0; sector < total2; sector++)
    {

        // Wait until data is ready
        error = ata_wait_drq(ata_io_base , ata_ctrl_base);
        if (error != FLUSHOS_EGOOD){
            pdisk->lba28_last_high = 0;
            return pata_handle_error(pdisk , error);
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
        return pata_handle_error(pdisk , error);
    }

    ata_send_command(ata_io_base , ata_ctrl_base ,CMD_LBA28_FLUSH_CACHE );
    // Wait until device is finished
    error = ata_wait_not_busy(ata_io_base , ata_ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->lba28_last_high = 0;
        return pata_handle_error(pdisk , error);
    }

    return FLUSHOS_EGOOD;
}
