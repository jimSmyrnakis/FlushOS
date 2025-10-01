#include "kernel.h"


int len  = 0;
void kernel_main(void){
    disable_intt();
    pic_remap(0x20 , 0x28);

    text_mode_init(coloured_display);
    char st[] = "Hello World !!! from kernel os ";
    text_mode_print_str(st, TM_DARK_BLUE);
    
    
    
    interrupts_init();
    text_mode_print_str(" Lol" , TM_DARK_BLUE);
    enable_intt();
    pic_enable_irq(1); // test keyboard interrupts :)
    
    
    




}