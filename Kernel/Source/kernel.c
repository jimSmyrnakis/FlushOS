#include "kernel.h"


int len  = 0;
extern void problem(void);
void kernel_main(void){
    text_mode_init(coloured_display);
    char st[] = "Hello World !!! from kernel os ";
    text_mode_print_str(st, TM_DARK_BLUE);
    text_mode_print_str(" Hello " , TM_DARK_BLUE) ;
    
    disable_intt();
    
    interrupts_init();
    text_mode_print_str(" Lol" , TM_DARK_BLUE);
    //enable_intt();
    

    outb(0xFF , 0x60 ); // teting ...




}