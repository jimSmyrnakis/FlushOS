#include "term.h"

Vga vgaValueOf(VgaChar character , VgaColour colour){
    
    return (Vga)((colour << 8) + character);
}
//returns a vga value that represents character and his colour

Vga*        vgaPtr;
uint16_t    vgaWidth;
uint16_t    vgaHeight; 
VgaColour   vgaColour;

void vgaInit(VgaColour colour){
    vgaPtr      = VGA_BEGIN;
    vgaColour   = colour;
    vgaWidth    = 0;
    vgaHeight   = 0;
} 

void vgaPrintChar(VgaChar ch ){
    if (ch == '\n'){
        vgaWidth  = 0;
        vgaHeight++;
        if (vgaHeight >= VGA_HEIGHT)
            vgaHeight = 0;
        return;
    }
    
    Vga element = vgaValueOf(ch , vgaColour);
    *(vgaPtr + vgaHeight*VGA_LENGTH + vgaWidth) = element;
    


    
    

    vgaWidth++;
    if (vgaWidth >= VGA_LENGTH){
        vgaWidth = 0;
        vgaHeight++;
    }
    if (vgaHeight >= VGA_HEIGHT){
        vgaWidth  = 0;
        vgaHeight = 0;
    }
    

}

void vgaPrintStr(VgaChar* str){
    int i = 0;
    while(str[i] != '\0'){
        vgaPrintChar(str[i]);
        i++;
    }
}

void vgaPrintPtr(uint32_t ptr){
    char symbols[16] = {
        '0' , '1' , '2' , '3' ,
        '4' , '5' , '6' , '7' ,
        '8' , '9' , 'A' , 'B' ,
        'C' , 'D' , 'E' , 'F' ,
    };

    char StringHex[11]  ;
    StringHex[10] = '\0';

    StringHex[0] = '0';
    StringHex[1] = 'x';

    int i = 0; 
    for (i = 0; i < 8 ; i++)
        StringHex[2 + i] = symbols[((ptr >> (28-i*4)) & 0x0000000F)];
    vgaPrintStr(StringHex);
}

void vgaClear(){
    int i,j;
    for(i = 0;i < VGA_HEIGHT ; i++)
        for( j = 0; j < VGA_LENGTH ; j++)
            *(vgaPtr + i*VGA_LENGTH + j) = 0;
    
    vgaHeight = 0;
    vgaWidth  = 0;
}