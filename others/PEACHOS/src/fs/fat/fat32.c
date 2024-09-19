#include "fat32.h"
#include <simple/string.h>



struct file_system fat32={
    .open     = fat16_open ,
    .resolve  = fat16_resolve
};

struct file_system* fat32_init(void){

    strcpy(fat32.name , "FAT 32 FS");
    return &fat32;
}

int fat32_resolve(struct disk* disk){
    return -1;
}

void* fat32_open(struct disk* disk,struct path_part* part , FILE_MODE mode){
    return KNULL;
}