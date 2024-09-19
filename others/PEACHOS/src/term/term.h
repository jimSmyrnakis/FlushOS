
#ifndef TERM_H
#define TERM_H 
#include <kernel.h>

typedef uint16_t Vga;
#define VGA_BEGIN  ((Vga*)0x000B8000)
#define VGA_LENGTH (80)
#define VGA_HEIGHT (20)
#define VGA_SIZE   (VGA_HEIGHT * VGA_LENGTH)
#define VGA_COUNT  (VGA_SIZE * sizeof(Vga))


typedef uint8_t VgaColour;
#define VGA_BLACK       ((VgaColour)0)
#define VGA_BLUE        ((VgaColour)1)
#define VGA_GREEN       ((VgaColour)2)
#define VGA_CYAN        ((VgaColour)3)
#define VGA_RED         ((VgaColour)4)
#define VGA_PURPLE      ((VgaColour)5)
#define VGA_BROWN       ((VgaColour)6)
#define VGA_GRAY        ((VgaColour)7)
#define VGA_DARKGARY    ((VgaColour)8)
#define VGA_LIGHTBLUE   ((VgaColour)9)
#define VGA_LIGHTGREEN  ((VgaColour)10)
#define VGA_LIGHTCYAN   ((VgaColour)11)
#define VGA_LIGHTRED    ((VgaColour)12)
#define VGA_LIGHTPURPLE ((VgaColour)13)
#define VGA_YELLOW      ((VgaColour)14)
#define VGA_WHITE       ((VgaColour)15)

typedef char VgaChar;

Vga vgaValueOf(VgaChar character , VgaColour colour);
//returns a vga value that represents character and his colour

void vgaInit(VgaColour colour);
//initialize the vga 

void vgaPrintChar(VgaChar ch );

void vgaPrintStr(VgaChar* str);

void vgaPrintPtr(uint32_t ptr);

void vgaClear();



#endif 