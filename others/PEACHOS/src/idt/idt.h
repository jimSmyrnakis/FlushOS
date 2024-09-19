#ifndef IDT_H
#define IDT_H


#include <def.h>
#include <status.h>
#include <config.h>
#include <term/term.h>
//structs for the system
struct idtPtr{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

struct idtDescriptor{
    uint16_t offset1;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  attr; 
    uint16_t offset2;
}__attribute__((packed));

typedef struct idtPtr           idtPtr          ;
typedef struct idtDescriptor    idtDescriptor   ;

//structs 

struct idtTable{
    idtDescriptor* entry;
    uint16_t size;
};

typedef struct idtTable idtTable;


//assembly functions
extern void disableInterrupts(void);
extern void enableInterrupts(void);
extern void loadIdtTable(idtPtr* ptr);
extern void storeIdtTable(idtPtr* pptr);
#define cli  disableInterrupts
#define sti  enableInterrupts
#define lidt loadIdtTable
#define sidt storeIdtTable

//c functions

/*
 * Initiallize the table by making a table to point on that entry
 * and setting it's size . If all goes well the function return's 
 * KERNEL_OK , else if size is zero return's ERR_BAD_ARGS value
 */ 
int idtInit(
    idtTable* pTable,
    idtDescriptor* entry ,
    idtDescriptor defaultDescriptor,
    uint16_t  size
);
/* 
 * Insert a new descriptor to the table at index position . 
 * If index is out of range , return's ERR_OUT_OF_RANGE else
 * if all ok return's KERNEL_OK
 */
int idtInsertInt(
    uint16_t index,
    idtDescriptor descriptor,
    idtTable* pTable 
);
/*
 * Removes a descriptor from the table at index position . 
 * If index is out of range , same as insert function .
 */
int idtRemoveInt(
    uint16_t        index   ,
    idtTable*       pTable  ,
    idtDescriptor defaultDescriptor,
    idtDescriptor*  desc
);
/*
 * Creates a new system struct that points to this table 
 * If the table has invalid size return's 
 * 
 */
int idtPointer(
    idtTable table ,
    idtPtr*  ppidt
);

idtDescriptor nullDescriptor(void);

/*int idtCreateDescriptor(
    void*    procedure ,
    uint16_t selector  ,
    uint8_t  isPresent ,
    uint8_t  disablingInterrupts
);*/

#endif 