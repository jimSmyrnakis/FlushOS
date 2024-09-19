#include "paging.h"
#include <term/term.h>

static uint32_t* currentDirectory = KNULL;

FlatModel* paging4GBFlatMap(PageFlags flags){
    uint32_t* dir = 
    (uint32_t*)kzalloc(PAGE_DIRECTORY_SIZE * sizeof(uint32_t));
    vgaPrintChar('|');
    vgaPrintPtr((uint32_t)dir);
    vgaPrintChar('|');
    if (dir == KNULL)
        return KNULL;

    uint32_t i , j;
    uint32_t* pageTable;
    uint32_t ppptr = 0;

    for( i = 0; i < PAGE_DIRECTORY_SIZE ; i++){
        dir[i] = (uint32_t)kzalloc(PAGE_TABLE_SIZE*sizeof(uint32_t));
        
        pageTable = (uint32_t*)dir[i];
        if (pageTable == KNULL)
            return KNULL;
        
        for ( j =0 ; j < PAGE_TABLE_SIZE ; j++){
            pageTable[j]  = ppptr;
            pageTable[j] |= flags;
            
            
            ppptr += (uint32_t)PAGE_SIZE;
        }

        dir[i] |= (flags);

    }
    FlatModel* paging = kzalloc(sizeof(FlatModel)) ;
    paging->directory = dir;
    return paging;
}

uint32_t* pagingGetDirectory(FlatModel mdl){
    return mdl.directory;
}


void pagingSwitchDirectory(uint32_t* newDirectory){
    loadPageDirectory(newDirectory);
    currentDirectory = newDirectory;
}

void pagingGetIndexes(
    void* virtualAddr ,
    uint32_t* pagingDirectoryIndex ,
    uint32_t* pagingTableIndex  ,
    uint16_t* pageOffset  
){

    if (pagingDirectoryIndex)
        (*pagingDirectoryIndex) = (((uint32_t)virtualAddr & 0xFFC00000) >> 22);
    if (pagingTableIndex)
        (*pagingTableIndex)     = (((uint32_t)virtualAddr & 0x003FF000)  >> 12);
    if (pageOffset)
        (*pageOffset)           = (((uint32_t)virtualAddr & 0x00000FFF));

}

void pagingSetVirtual(
    uint32_t* directory ,
    void* virtualAddr ,
    uint32_t val 
){
    uint32_t di , ti ;
    pagingGetIndexes(virtualAddr , &di , &ti , KNULL);

    uint32_t* table = (uint32_t*)(((uint32_t)directory[di]) & 0xFFFFF000);
    table[ti] = val & 0xFFFFF000;

}