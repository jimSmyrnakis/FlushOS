#ifndef _KERNEL_H_
#define _KERNEL_H_

// all includes needed :)
#include "Interrupts/interrupts.h"
#include "./drivers/mono/desktop/text_mode/text_mode.h"
#include "io/io.h"
#include "heap/kheap.h"
#include "paging/paging.h"
#include "virtmem/virtmem.h"
#include "drivers/mono/desktop/pic/pic.h"
#include "disk/disk.h"
#include "disk/disk_stream.h"
#include "file_system/path_parser.h"
#include "file_system/file.h"
#include "std/string.h"
#include "print.h"
#include "common_defs.h"
#include "panic.h"

void kernel_main(void);


#endif 
