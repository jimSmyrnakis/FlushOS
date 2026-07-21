#include "../../../../errno.h"
#include "pata.h"
#include <print.h>
#include "pata_registers.h"
#include "pata_special_cmds.h"
#define ATA_TIMEOUT 1000000

void ata_delay_400ns(uint16_t ATA_CTRL_BASE ){
    uint8_t status ;

    // wait to be ready 
    for (int i = 0; i < 5 ; i++)
        inb(&status , ATA_CTRL_BASE + ALTERNATE_STATUS);
}

void ata_delay_5us(uint16_t ATA_CTRL_BASE ){
    uint8_t status ;

    // wait to be ready 
    for (int i = 0; i < 100 ; i++)
        inb(&status , ATA_CTRL_BASE + ALTERNATE_STATUS);
}


uint32_t ata_get_logical_sector_size(uint16_t* identify)
{
    uint16_t word106 = identify[IDENTIFY_WORD_LOGICAL_SECTOR_INFO];

    /*
        Bit 14 = words 117-118 are valid
    */
    if (!(word106 & IDENTIFY_WORD_106_VALID))
    {
        // ATA default logical sector size
        return 512;
    }


    uint32_t sector_size =
        ((uint32_t)identify[IDENTIFY_WORD_LOGICAL_SECTOR_SIZE_LOW]) |
        ((uint32_t)identify[IDENTIFY_WORD_LOGICAL_SECTOR_SIZE_HIGH] << 16);


    /*
        Safety check
        Logical sector size must be reasonable
    */
    if (sector_size == 0)
        return 512;


    return sector_size;
}


errno ata_check_status(uint8_t status)
{
    if(status & STATUS_ERROR)
        return FLUSHOS_EIO;

    if(status & STATUS_DRIVE_FAULT)
        return FLUSHOS_EHWFAIL;

    return FLUSHOS_EGOOD;
}

errno ata_get_error(uint16_t io_base)
{
    uint8_t error;

    inb(&error, io_base + ERROR_REGISTER);

    if(error & UNC)
        return FLUSHOS_EDTCRPT;

    if(error & BBK)
        return FLUSHOS_EBBLCK;

    if(error & ABRT)
        return FLUSHOS_EIO;

    if(error & MCR)
        return FLUSHOS_ERMVD;
    
    if(error & MC)
        return FLUSHOS_ERMVD;

    if (error & IDNF)
        return FLUSHOS_EOOB;

    if (error & AMNF)
        return FLUSHOS_EHWFAIL;

    if (error & TKZNF)
        return FLUSHOS_EHWFAIL;

    return FLUSHOS_EUNKNOWN;
}

errno ata_soft_reset(
    uint16_t io_base,
    uint16_t ctrl_base
)
{
    outb(SRST, ctrl_base + DEVICE_CONTROL);
    ata_delay_5us(ctrl_base);

    outb(NIEN, ctrl_base + DEVICE_CONTROL);

    errno err = ata_wait_not_busy(io_base, ctrl_base);
    if(err != FLUSHOS_EGOOD)
        return err;

    return ata_wait_ready(io_base, ctrl_base);
}

errno ata_wait(uint16_t io_base , uint16_t ctrl_base , uint8_t wait_set , uint8_t wait_clear){
    uint8_t status = 0;
    int timeout = ATA_TIMEOUT;
    do {
        inb(&status , io_base + STATUS_REGISTER);
        errno err = ata_check_status(status);
        if (err == FLUSHOS_EIO){
            return ata_get_error(io_base);
        }
        if (err == FLUSHOS_EHWFAIL){
            return FLUSHOS_EHWFAIL;
        }


        if (timeout <= 0) return FLUSHOS_ETIMEOUT;


        timeout--;
    }while (
        (status & wait_clear) ||
        (wait_set && ((status & wait_set) != wait_set))
    );

    return FLUSHOS_EGOOD;
}

errno ata_wait_ready(uint16_t io_base , uint16_t ctrl_base){
    return ata_wait(
        io_base , ctrl_base , STATUS_DRIVE_READY , STATUS_DRIVER_BUSY
    );
    
}

errno ata_wait_not_busy(uint16_t io_base , uint16_t ctrl_base){
    return ata_wait(
        io_base, ctrl_base ,
        0,
        STATUS_DRIVER_BUSY);
}


errno ata_wait_drq(uint16_t io_base , uint16_t ctrl_base){
    return ata_wait(
        io_base, ctrl_base ,
        STATUS_PIO_READY,
        STATUS_DRIVER_BUSY);
}

void ata_send_command(uint16_t io_base , uint16_t ctrl_base , uint8_t cmd ){
    outb(cmd , io_base + COMMAND_REGISTER);
}

errno ata_recover(
    uint16_t io_base,
    uint16_t ctrl_base,
    uint8_t select_drive 
)
{
    
    errno err = ata_soft_reset(io_base , ctrl_base);

    ata_wait_not_busy(io_base , ctrl_base);

    // select drive again
    outb(select_drive | LBA | 0xA0, io_base + DRIVE_REGISTER);

    ata_delay_400ns(ctrl_base);

    ata_wait_ready(io_base , ctrl_base);

    uint8_t val;

    return err;
}
    


