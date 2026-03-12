#ifndef GPSPCPU_VPGS_H
#define GPSPCPU_VPGS_H

    #include "../core.h"

    /*
     *
     *
     * Note :   VPGS or Virtual Paging System is a generic paging mechanism that will be used for the operating system .
     *          Even if the processor supports multiple level paging this mechanism must use it as a single paging level (only page table with all mapping ) 
     *          the reason is simple "With one paging level every multiple paging level given by a specific processor and specific versions of this cpu 
     *          is easy to implement , but in a multyple paging vpgs a single paging mechanism from processor side is not able to implement or makes the work 
     *          very hard "
     *          The best approach is to use big paging frames even if the cpu specific paging mechanism has small one's as the O.S. is target for gaming console .
     *          Best recomended page frame size is 64KB as that big page/block will be used by the File System . Every paging
     *          table entry or pte must be power of two allign (1K , 2K , 4K , 8K , 16K , .. , 64K , 128K , ... , 1MB ) , plus every implementation must specifie
     *          a multyple of the page frame .
     *          For examble if a 2 level paging mechanism is used (as intel's pentium I has ) every level is multyple of the first level pages (the intel's pentium I
     *          has 4KB page frames but every paging directory entry points to 1024 pte , that means by using this mechanism a 4MB page frame will used here ) . But
     *          problems in perfomance can still happen , for examble on intel's level 2 (pde) we dont have a dirty bit but only in level 1 (pte) . That means that
     *          for intel's Pentium I we must search for set dirty bit on every pte on the pde , se we can decide "Do i need to write this page on disk ?" 
     *          (hdd , sdd , flash mem etc.) 
     *          A third node is to allign all page frames on the last level (level 1) , otherwise all info by GPSPCPU_pte are rong . From intel's examble we sayed that 
     *          level 1 (pte's) are 4KB , but we will used 4MB because 2 Level paging is used and from level 2 perspective the paging size is 4MB 
     *          (1024 pte's * 4KB frames size = 4MB) . That means that all 1024 pte's point to one allign 4MB page where each pte points to its own 4KB page frame , if 
     *          that not happen then the GPSPCPU_pte point's to rong base physical address as this 4MB page is in peaces of 4KB , in that case we must define as a 4KB
     *          page frame's not 4MB . (all these notes are for implementations not for use ) 
    */

    struct GPSPCPU_paging{
        GPSPCPU_addr ptble; // paging table physical address
        GPSPCPU_u32b limit; // paging table limit (last byte starting from ptble)
        GPSPCPU_u16b pfsiz; // page frame size
        GPSPCPU_u8b  type ; // paging type noted based on processor (given by calls to specific implementation's )
    };

    struct GPSPCPU_pte{
        GPSPCPU_addr phyaddr;   // tha physical address on where the page is on memory
        GPSPCPU_addr viraddr; 

    };

#endif 