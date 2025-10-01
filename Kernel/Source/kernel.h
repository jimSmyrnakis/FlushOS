#ifndef _KERNEL_H_
#define _KERNEL_H_

// all includes needed :)
#include "Interrupts/interrupts.h"
#include "./drivers/mono/desktop/text_mode/text_mode.h"
#include "io/io.h"
#include "Interrupts/pic.h"
void kernel_main(void);

#endif 
