#ifndef __FLUSHOS_PRINT_H__
#define __FLUSHOS_PRINT_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include "drivers/mono/desktop/text_mode/text_mode.h"

#define print(str) text_mode_print_str((str) , TM_DARK_BLUE)
#define printc(c)  text_mode_write_char((c) , TM_DARK_BLUE)
    void printHex(void* ptr);
#endif 