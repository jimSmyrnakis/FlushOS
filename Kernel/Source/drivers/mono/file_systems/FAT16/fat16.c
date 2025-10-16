#include "fat16.h"
#include "../../../../std/string.h"

#include "fat16_common.c"

struct file_system fat16_fs = {
    .open = fat16_open,
    .resolve = fat16_resolve
};

struct file_system* fat16_init(void){
    strncpy( fat16_fs.name  , "FAT16" , 6);

    return &fat16_fs;
}

void* fat16_open(struct disk* disk, struct path_part * part, file_mode bit_mode){
    // not implemented yet
    return NULL;
}

// i find more usefull to have these in seperated files for simplicity and readability
// reasons , but compilation is happen in one file with all of them together once
#include "resolve/resolve.c" 