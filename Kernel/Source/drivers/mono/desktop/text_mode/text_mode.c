#include "text_mode.h"
#include <stdint.h>
#include <stddef.h>
#include "../../../../std/string.h"

uint16_t* vga_tm_entry = 0;
uint16_t vga_tm_current_row = 0;
uint16_t vga_tm_current_col = 0;


uint16_t text_mode_make_char(char c , enum text_mode_colour colour ){
    
    return (colour << 8) | c;
}

void text_mode_put_char(uint8_t col , uint8_t row , char ch , enum text_mode_colour colour){
    uint16_t val = text_mode_make_char(ch , colour);
    
    vga_tm_entry[ row* VGA_WIDTH + col ] = val; 
}

void text_mode_init(enum text_mode_display display_type){
    switch(display_type){
        case coloured_display : 
        {
            vga_tm_entry = (uint16_t*)0xB8000;
            break;
        }
        case monochrome_display :
        {
            vga_tm_entry = (uint16_t*)0xB0000;
            break;
        }
    }

    // clear all the previus text
    for(int i = 0 ; i< VGA_HEIGHT ; i++){
        for(int j = 0 ; j< VGA_WIDTH; j++){
            text_mode_put_char((uint8_t)j , (uint8_t)i , ' ' , 0);
        }
    }

    // initiallize state
    vga_tm_current_row = 0;
    vga_tm_current_col = 0;
    return;
}



void text_mode_write_char(char ch , enum text_mode_colour colour){
    if (ch == '\n')
        vga_tm_current_col = VGA_WIDTH;
    else 
        text_mode_put_char(vga_tm_current_col , vga_tm_current_row , ch , colour);

    vga_tm_current_col++;
    if (vga_tm_current_col >= VGA_WIDTH){
        vga_tm_current_row++;
        vga_tm_current_col = 0;
        if (vga_tm_current_row >= VGA_HEIGHT){
            vga_tm_current_row = 0;
        }
    }
}

void text_mode_print_str(const char* str , enum text_mode_colour colour){
    size_t len = strlen(str);
    for(int i = 0; i < len ; i++){
        text_mode_write_char(str[i] , colour);
    }
}