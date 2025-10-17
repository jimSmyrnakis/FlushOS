#ifndef __FAT16_RESOLVE_COMMON_C__
#define __FAT16_RESOLVE_COMMON_C__

    #include "inc.h"

    static bool is_fat16_header(struct fat16_header header){
        bool check = 
        (header.bios_parameter_block.fat_copies == 1) || 
        (header.bios_parameter_block.fat_copies);

        check = check && 
        (
            (header.extended_bios_parameter_block.signature == 0x29) ||
            (header.extended_bios_parameter_block.signature == 0x28)
        );

        

        return check;
    } 

    

    
#endif 