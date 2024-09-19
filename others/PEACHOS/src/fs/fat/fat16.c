#include "fat16.h"
#include <simple/string.h>

struct file_system fat16 = {
    .resolve = fat16_resolve,
    .open    = fat16_open
};

struct file_system* fat16_init(void){

    strcpy(fat16.name , "FAT16");
    return &fat16;
}

int fat16_resolve(struct disk* disk){
    return 0;
}

void* fat16_open(struct disk* disk,struct path_part* part , FILE_MODE mode){
    return KNULL;
}
