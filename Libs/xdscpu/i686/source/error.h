#ifndef X86_32_ERROR_H
    #define X86_32_ERROR_H
    #include <stdint.h>
    #include <stddef.h>

    typedef uint16_t x86_32_err_type ;

    //error's !!!
    #define X86_32_E_OOR                        ((x86_32_err_type) 0x0001)
    #define X86_32_E_OK                         ((x86_32_err_type) 0x0000)
    #define X86_32_E_SEGMENT_LIMIT_OOB          ((x86_32_err_type) 0x0002)
    #define X86_32_E_SEGMENT_LIMIT_INVALID      ((x86_32_err_type) 0x0003) // limit greater than 1MB must be multyple of 4KB values 
    #define X86_32_E_INVALID_DESCRIPTOR_TYPE    ((x86_32_err_type) 0x0004) // for examble you try to open the descriptor as code segment but is not
    #define X86_32_E_GDT_BAD_LIMIT              ((x86_32_err_type) 0x0005) // limit for set in gdt descriptor is not give a size multyple of that of descriptor
    #define X86_32_E_GDT_UNITIALLIZED           ((x86_32_err_type) 0x0006)
    #define X86_32_E_INDEX_OOB                  ((x86_32_err_type) 0x0007)
    #define X86_32_E_GDT_BAD_SIZE               ((x86_32_err_type) 0x0008)
    #define X86_32_E_GDT_NO_MEMORY              ((x86_32_err_type) 0x0009)
    #define X86_32_E_GDT_TOO_SMALL              ((x86_32_err_type) 0x000A)
    #define X86_32_E_GDT_OOAS                   ((x86_32_err_type) 0x000B) // out of addressable space
    #define X86_32_E_INVALID_GDT_SIZE           ((x86_32_err_type) 0x000C)
    #define X86_32_E_PAGE_DIR_NOT_ALLIGN        ((x86_32_err_type) 0x000D) // page directory must be 4KB allign
    #define X86_32_E_BPFA                       ((x86_32_err_type) 0x000E) // bad page frame alligment
    #define X86_32_E_BPTA                       ((x86_32_err_type) 0x000F) // bad page table alligment 
    #define X86_32_E_TSS32LMTSML                ((x86_32_err_type) 0x0010) // tss32 limit small
    #define X86_32_E_BSGMNTSPC                  ((x86_32_err_type) 0x0011) // bad segment space
    #define X86_32_E_SMLSPC                     ((x86_32_err_type) 0x0012) // SMALL SPACE
    #define X86_32_E_BADPARAM                   ((x86_32_err_type) 0x0013) // BAD PARAMETER
    #define X86_32_E_GDTANLDESCR                ((x86_32_err_type) 0x0014) // write to gdt null descriptor (index = 0)
    #define X86_32_E_IORSVDPORT                 ((x86_32_err_type) 0x0015) // io address reserved range [0x00F8 , 0x00FF]
    #define X86_32_E_IOBADPORT                  ((x86_32_err_type) 0x0016) 

    //warning's !
    #define X86_32_W_BAD_GDT_PERFOMANCE         ((x86_32_err_type) 0x1000)
    #define X86_32_W_IOBADALGN                  ((x86_32_err_type) 0x1001) // io port/address is not alligned to the size of data (in or out)
    #define X86_32_W_ZRCNT                      ((x86_32_err_type) 0x1002) // count of a buffer is zero
#endif