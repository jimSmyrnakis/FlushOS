#ifndef _DRIVERS_MONO_TEXT_MODE_H_
#define _DRIVERS_MONO_TEXT_MODE_H_

    
    #include <stdint.h>
#include <stddef.h>
    // definitions

    #define VGA_HEIGHT 20
    #define VGA_WIDTH  80
    

    enum text_mode_colour{
        TM_BLACK ,
        TM_DARK_BLUE = 1
        
    };
    enum text_mode_display{
        coloured_display ,
        monochrome_display
    };
    size_t strlen(const char* text);
    void text_mode_clear(void);
    void text_mode_init(enum text_mode_display display_type);
    void text_mode_write_char(char ch , enum text_mode_colour colour);
    void text_mode_put_char(uint8_t col , uint8_t row , char ch , enum text_mode_colour colour);
    void text_mode_print_str(const char* str , enum text_mode_colour colour);
#endif 