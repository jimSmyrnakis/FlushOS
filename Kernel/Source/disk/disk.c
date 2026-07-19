#include "disk.h"
#include "../std/memory.h"
#include "../drivers/mono/desktop/pata/pata.h"
#include "../errno.h"
#include "../file_system/file.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#define MAX_DISKS_COUNT 64

struct disk disk_array[MAX_DISKS_COUNT];
bool is_available[MAX_DISKS_COUNT];
uint16_t total_disks = 0;

#ifndef NULL
#define NULL ((void*)0)
#endif 

void disk_init(void){
    memset(disk_array , 0 , sizeof(disk_array));
    for(int i=0;i<MAX_DISKS_COUNT;i++)
    {
        is_available[i]=true;
    }
    total_disks = 0;
}

static int get_next_available_slot(void){
    for (int i = 0; i < MAX_DISKS_COUNT; i++)
    {
        if (is_available[i] == true)
            return i;
    }

    return -1;
}



errno disk_create(
        struct disk_module* module , 
        void* priv , struct disk_attributes attrs){
    if (module == NULL)
        return FLUSHOS_EBADARG;

    if (
        !module->read   || 
        !module->write  ){

        return FLUSHOS_EBADDISK;
    }

    // find first available slot
    int index = get_next_available_slot();
    if (index < 0 )
        return FLUSHOS_EOOB;


    // create disk and initialized it 
    errno err = FLUSHOS_EGOOD;
    memset(&disk_array[index] , 0 , sizeof(struct disk));
    is_available[index] = false;
    total_disks++;
    disk_array[index].module = *module;
    disk_array[index].id = index;
    disk_array[index].attrs = attrs;
    disk_array[index].priv = priv;
    // now make call back to virtual file system so it can attach a file system 
    // if possible . In Future we can add partiotioning by adding partitioning
    // manager that creates virtual disks as real ones , attach them with 
    // a file system and mark them as file system supported and the actuall disk driver
    // as not . 
    disk_array[index].fs = fs_resolve(&disk_array[index]);



    
    return FLUSHOS_EGOOD;
}

errno disk_destroy(struct disk* idisk){
    if (!idisk) return FLUSHOS_EBADARG;
    int index = idisk->id;

    if ( (index >= MAX_DISKS_COUNT) || (index < 0) || (is_available[index] == true) ){
        return FLUSHOS_EBADDISK;
    }

    if (idisk != &disk_array[index])
        return FLUSHOS_BADSTRCT;
    
    

    // thearetycly here should call file system callback to unmount 
    // first and then finalized the disk . 
 


    // then free slot 
    is_available[index] = true;
    total_disks--;
    memset(&disk_array[index] , 0 , sizeof(struct disk));

    return FLUSHOS_EGOOD;
}


errno disk_read( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer ){
    if (!idisk) return FLUSHOS_EBADARG;
    int index = idisk->id;

    if ( (index >= MAX_DISKS_COUNT) || (index < 0) || (is_available[index] == true) ){
        return FLUSHOS_EBADDISK;
    }

    if (idisk != &disk_array[index])
        return FLUSHOS_BADSTRCT;
    
    errno res = idisk->module.read(lba , total , buffer, idisk->priv);
   
    return res;
}

errno disk_write( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer){
    if (!idisk) return FLUSHOS_EBADARG;
    int index = idisk->id;

    if ( (index >= MAX_DISKS_COUNT) || (index < 0) || (is_available[index] == true) ){
        return FLUSHOS_EBADDISK;
    }

    if (idisk != &disk_array[index])
        return FLUSHOS_BADSTRCT;
    
    errno res = idisk->module.write(lba , total , buffer , idisk->priv);
    
    
    return res;
}




struct disk* disk_get(int index){
    if ( (index >= MAX_DISKS_COUNT) || (index < 0) || (is_available[index] == true) ){
        return NULL;
    }

    return &disk_array[index];
}


uint16_t disk_get_max_disks(void){
    return MAX_DISKS_COUNT;
}
    
uint16_t disk_get_disks_count(void){
    return total_disks;
}

uint32_t disk_get_id(struct disk* idisk){
    return idisk->id;
}
