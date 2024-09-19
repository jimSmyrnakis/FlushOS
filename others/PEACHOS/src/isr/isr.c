#include "isr.h"


void handler0(void)
{
    vgaClear();
    vgaPrintStr("Division with zero , please carefull :)\n");
    outb(0x20,0x20);
}
void defaultHandler(void){
    outb(0x20,0x20);
}
void handler21(void){
    vgaClear();
    vgaPrintStr("Keyboard is pressed");
    outb(0x20,0x20);
}
static idtTable tbl;
static idtDescriptor desc;
static idtPtr idtr;

int ISR_init(idtDescriptor* idt , uint16_t size){
    cli();


    desc.zero       = 0;
    desc.offset1    = (((uint32_t)idtDefaultHandler) & 0x0000FFFF);
    desc.offset2    = ((((uint32_t)idtDefaultHandler) & 0xFFFF0000) >> 16); 
    desc.selector   = (0x08);
    desc.attr       = 0b10001111;
    if (idtInit(&tbl , idt ,desc , size)!= KERNEL_OK)
        return errno();
    
    

    desc.offset1    = (((uint32_t)idtHandler0) & 0x0000FFFF);
    desc.offset2    = ((((uint32_t)idtHandler0) & 0xFFFF0000) >> 16); 
    if (idtInsertInt(0, desc, &tbl ) != KERNEL_OK)
        return errno();
    
    desc.offset1    = (((uint32_t )KEYBOARD_HANDLER) & 0x0000FFFF);
    desc.offset2    = ((((uint32_t)KEYBOARD_HANDLER) & 0xFFFF0000) >> 16); 
    if ( idtInsertInt(0x21, desc, &tbl ) != KERNEL_OK)
        return errno();
    

    if (idtPointer(tbl , &idtr) != KERNEL_OK)
        return errno();

    lidt(&idtr);
    return errno();
}