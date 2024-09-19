#ifndef PAGING_H
#define PAGING_H

#include <def.h>
#include <status.h>
#include <config.h>
#include "kheap.h"
typedef uint8_t PageFlags ;
#define PAGING_ACCESED       ((PageFlags)0b00100000)
#define PAGING_DISABLE_CACHE ((PageFlags)0b00010000)
#define PAGING_WRITE_THROUGH ((PageFlags)0b00001000)
#define PAGING_ACCESS_FREE   ((PageFlags)0b00000100)
#define PAGING_WRITABLE      ((PageFlags)0b00000010)
#define PAGING_PRESENT       ((PageFlags)0b00000001)


#define PAGE_SIZE (4096)
#define PAGE_TABLE_SIZE (1024)
#define PAGE_DIRECTORY_SIZE (1024)

//assembly functions
extern void loadPageDirectory(uint32_t* dir);
extern void storePageDirectory(uint32_t* dir);
extern void enablePaging(void);
extern void disablePaging(void);
#define lpgd loadPageDirectory
#define spgd storePageDirectory
#define clp  disablePaging
#define stp  enablePaging





struct FlatModel{
    uint32_t*  directory;
};
typedef struct FlatModel FlatModel;

FlatModel* paging4GBFlatMap(PageFlags flags);

uint32_t* pagingGetDirectory(FlatModel mdl);

void pagingSwitchDirectory(uint32_t* newDirectory);

#define pagingIsAllinged(addr) (( ((uint32_t)(addr)) % PAGE_SIZE ) == 0)

void pagingGetIndexes(
    void* virtualAddr ,
    uint32_t* pagingDirectoryIndex ,
    uint32_t* pagingTableIndex ,
    uint16_t* pageOffset  
);

void pagingSetVirtual(
    uint32_t* directory ,
    void* virtualAddr ,
    uint32_t val 
);







#endif