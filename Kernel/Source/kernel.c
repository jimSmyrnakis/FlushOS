#include "kernel.h"

#include "./drivers/mono/desktop/text_mode/text_mode.h"
int len  = 0;
void kernel_main(void){
    text_mode_init(coloured_display);
    char st[] = "Hello World !!! from kernel os ";
    text_mode_print_str(st, TM_DARK_BLUE);
    text_mode_print_str(" Hello " , TM_DARK_BLUE) ;
}