#include "disk.h"
#include "../std/memory.h"
#include "../drivers/mono/desktop/pata/pata.h"
#include "../errno.h"

struct disk disk_array[1];

#ifndef NULL
#define NULL ((void*)0)
#endif 

void disk_init(void){
    memset(disk_array , 0 , sizeof(struct disk));

    // for the time being , only pata primary is supported :(
    disk_array[0].sector_size = 512;
    disk_array[0].type = DISK_TYPE_PATA_PRIMARY;
    disk_array[0].read_function = pata_read_sector;
    // any other disk like other PATA and SATA will implemented in the future 
    // when the main focus will be them :)

}


struct disk* disk_get(int index){
    if (index > 0 )
        return NULL;

    return &disk_array[index];
}

errno disk_read_sector( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer ){
    if (idisk != &disk_array[0])
        return FLUSHOS_EBADARG;
    
    errno res = idisk->read_function(lba , total , buffer);
    if (res != FLUSHOS_EGOOD)
        return res;
    
    return FLUSHOS_EGOOD;
}