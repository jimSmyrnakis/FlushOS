#include "fat16.h"
#include "../../../../std/string.h"

#include "common.c"



struct file_system* fat16_init(void){
    strncpy( fat16_fs.name  , "FAT16" , 6);

    return &fat16_fs;
}



// i find more usefull to have these in seperated files for simplicity and readability
// reasons , but compilation is happen in one file with all of them together once
#include "resolve/resolve.c" 
#include "open/open.c"
