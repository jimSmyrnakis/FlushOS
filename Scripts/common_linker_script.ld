ENTRY(kernel_init)
OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 1M ;/* this actually says our first address in memory is 0x100000 or after 1MB memory (exacly after real mode max addressable space) */

    .text : ALIGN(4096)
    {
        *(.text)
    }

    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }

    .data : ALIGN(4096)
    {
        *(.data)
    }

    .bss : ALIGN(4096)
    {
        *(COMMON)
        *(.bss)
    }

    .asm : ALIGN(4096)
    {
        *(.asm)
    }

}