#include "fat16.h"
#include "../../../../std/string.h"

struct file_system fat16_fs = {
    .open = fat16_open,
    .resolve = fat16_resolve
};

struct file_system* fat16_init(void){
    strncpy( fat16_fs.name  , "FAT16" , 6);

    return &fat16_fs;
}

void* fat16_open(struct disk* disk, struct path_part * part, file_mode bit_mode){
    return NULL;
}
    
errno fat16_resolve(struct disk* disk){

    
    return FLUSHOS_ENIMPL;
}