#ifndef ISR_H
#define ISR_H

#include <def.h>
#include <status.h>
#include <config.h>
#include <idt/idt.h>
#include <term/term.h>
#include <io/io.h>

extern void idtHandler0(void);
extern void idtHandler21(void);
extern void idtDefaultHandler(void);

void handler0(void);
void defaultHandler(void);
void handler21(void);

#define KEYBOARD_HANDLER idtHandler21

int ISR_init(idtDescriptor* idt , uint16_t size);

#endif 