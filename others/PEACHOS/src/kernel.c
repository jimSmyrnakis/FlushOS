#include "kernel.h"
#include "term/term.h"
#include "idt/idt.h"
#include "io/io.h"
#include "isr/isr.h"
#include "kheap.h"
#include "paging/paging.h"
#include "fs/file.h"
#include "fs/fat/fat16.h"
#include "fs/pparser.h"
#include "disk/stream.h"

extern void makeProblem(void);


static idtDescriptor idt[IDT_TABLE_SIZE];
static VgaColour clr;

void kmain(void){
    cli();
    //initiallize terminal
    clr = VGA_LIGHTGREEN;
    vgaInit(clr);
    vgaClear();
    vgaPrintStr("Hello World \n");
    
    // initiallize heap
    initKernelHeap();
    if (errno() != KERNEL_OK){
        char* msg = "heap failed to initiallize";
        vgaPrintStr(msg);
        return ;
    }

    //initiallize file systems
    fs_init();

    //initiallize interrupts
    ISR_init(idt , IDT_TABLE_SIZE);
    if (errno() != KERNEL_OK){
        char* msg = "ISR failed to initiallize";
        vgaPrintStr(msg);
        return;
    }
    

    //initiallize paging
    vgaPrintStr("Hello World dfsdffdgfdsfd\n");
    FlatModel* pages = paging4GBFlatMap(
        PAGING_ACCESS_FREE  |
        PAGING_PRESENT      |
        PAGING_WRITABLE     
    );
    if (pages == KNULL){
        char* msg = "paging failed to initiallize";
        vgaPrintStr(msg);
        return ;
    }
    
    pagingSwitchDirectory(pagingGetDirectory(*pages));
    

    stp();// enable paging michanism/**/
    sti();//enable interrupts

    disk_search_and_init();

    
    while(1) ;
    


}


