#ifndef __FLUSHOS_PATA_SPECIAL_CMDS_H__
#define __FLUSHOS_PATA_SPECIAL_CMDS_H__
#include <stdint.h>
#include <stddef.h>
void ata_delay_400ns(uint16_t ATA_CTRL_BASE );
errno ata_check_status(uint8_t status);
uint32_t ata_get_logical_sector_size(uint16_t* identify);
errno ata_get_error(uint16_t io_base);
errno ata_soft_reset(
    uint16_t io_base,
    uint16_t ctrl_base
);
errno ata_wait_ready(uint16_t io_base , uint16_t ctrl_base);
errno ata_wait_not_busy(uint16_t io_base , uint16_t ctrl_base);
errno ata_wait_drq(uint16_t io_base , uint16_t ctrl_base);
void ata_send_command(uint16_t io_base , uint16_t ctrl_base , uint8_t cmd );
errno ata_recover(
    uint16_t io_base,
    uint16_t ctrl_base,
    uint8_t select_drive 
);
#endif 