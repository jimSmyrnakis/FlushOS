#=============basic paths====================
source_path=../source
object_path=../object
library_path=../library
include_path=../include
#=============basic paths====================




#===================final debug/release library object file====================
library_file= $(library_path)/x86_32_proc.o
#===================final debug/release library object file====================





#===============compiler/assembler calls===================
#compiler and flag's
cc=i686-elf-gcc
cc_flags1= -g -Wno-address-of-packed-member -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer 
cc_flags2= -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs 
cc_flags= $(cc_flags1) $(cc_flags2) -Wall -O0  -std=gnu99
#assembler and flag's
asm=nasm
asm_flags= -g -f elf
#linker and flag's
ld=i686-elf-ld
ld_flags= -g -relocatable
#===============compiler/assembler calls===================







#==================== object files locations ====================
#selector
selector_c_obj= $(object_path)/selector/selector.c.o
selector_obj= $(selector_c_obj)
#io
io_asm_obj= $(object_path)/io/io.asm.o
io_c_obj= $(object_path)/io/io.c.o
io_obj= $(io_asm_obj) $(io_c_obj)
#pde
pde_c_obj= $(object_path)/paging/pde.c.o
pde_obj= $(pde_c_obj)
#pte
pte_c_obj= $(object_path)/paging/pte.c.o
pte_obj= $(pte_c_obj)
#pgdr
pgdr_c_obj= $(object_path)/paging/pgdr.c.o
pgdr_obj= $(pgdr_c_obj)
#pgcr
pgcr_c_obj= $(object_path)/paging/pgcr.c.o
pgcr_obj= $(pgcr_c_obj)
#control registers
rcontrol_c_obj= $(object_path)/registers/control/control.c.o
rcontrol_asm_obj= $(object_path)/registers/control/control.asm.o
rcontrol_obj= $(rcontrol_asm_obj) $(rcontrol_c_obj)
#eflags registers
eflags_c_obj= $(object_path)/registers/eflags/eflags.c.o
eflags_asm_obj= $(object_path)/registers/eflags/eflags.asm.o
eflags_obj= $(eflags_asm_obj) $(eflags_c_obj)
#segment registers
rsegment_c_obj= $(object_path)/registers/segment/segment.c.o
rsegment_asm_obj= $(object_path)/registers/segment/segment.asm.o
rsegment_obj= $(rsegment_asm_obj) $(rsegment_c_obj)
#system registers
rsystem_c_obj= $(object_path)/registers/system/system.c.o
rsystem_asm_obj= $(object_path)/registers/system/system.asm.o
rsystem_obj= $(rsystem_asm_obj) $(rsystem_c_obj)
#debug registers
debug_c_obj= $(object_path)/registers/debug/debug.c.o
debug_asm_obj= $(object_path)/registers/debug/debug.asm.o
debug_obj= $(debug_asm_obj) $(debug_c_obj)
#interrupt
interrupt_asm_obj= $(object_path)/interrupt/interrupt.asm.o
interrupt_obj= $(interrupt_asm_obj)
#farcalls
farcalls_asm_obj= $(object_path)/farcalls/farcalls.asm.o
farcalls_c_obj= $(object_path)/farcalls/farcalls.c.o
farcalls_obj= $(farcalls_asm_obj) $(farcalls_c_obj)
#ecode
ecode_asm_obj= $(object_path)/ecode/ecode.asm.o
ecode_c_obj= $(object_path)/ecode/ecode.c.o
ecode_obj= $(ecode_asm_obj) $(ecode_c_obj)
#descriptors
descriptors_obj= $(object_path)/descriptors/descriptors.c.o
#segment
segment_obj= $(object_path)/descriptors/segment/segment.c.o
#data
data_obj= $(object_path)/descriptors/segment/data.c.o
#code
code_obj= $(object_path)/descriptors/segment/code.c.o
#call_gate32
call_gate32_obj= $(object_path)/descriptors/system/call_gate32.c.o
#intt_gate32
intt_gate32_obj= $(object_path)/descriptors/system/intt_gate32.c.o
#trap_gate32
trap_gate32_obj= $(object_path)/descriptors/system/trap_gate32.c.o
#task_gate32
task_gate32_obj= $(object_path)/descriptors/system/task_gate32.c.o
#tss32d
tss32d_obj= $(object_path)/descriptors/system/tss32d.c.o
#ldtd
ldtd_obj= $(object_path)/descriptors/system/ldtd.c.o
#dtables
dtables_obj= $(object_path)/dtables/dtables.c.o
#idt
idt_c_obj= $(object_path)/dtables/idt/idt.c.o
idt_asm_obj= $(object_path)/dtables/idt/idt.asm.o
idt_obj= $(idt_asm_obj) $(idt_c_obj)
#ldt
ldt_c_obj= $(object_path)/dtables/ldt/ldt.c.o
ldt_obj= $(ldt_c_obj)
#gdt
gdt_c_obj= $(object_path)/dtables/gdt/gdt.c.o
gdt_asm_obj= $(object_path)/dtables/gdt/gdt.asm.o
gdt_obj= $(gdt_asm_obj) $(gdt_c_obj)
#atom
atom_asm_obj= $(object_path)/atom/atom.asm.o
atom_obj= $(atom_asm_obj)
#all object files
object_files1= $(selector_obj) $(io_obj) $(pgdr_obj) $(pgcr_obj) $(pte_obj) $(pde_obj) $(rcontrol_obj) $(eflags_obj) $(rsegment_obj) $(rsystem_obj) $(rdebug_obj)
object_files2= $(interrupt_obj) $(farcalls_obj) $(ecode_obj) $(descriptors_obj) $(segment_obj) $(data_obj) $(code_obj) $(call_gate32_obj) $(atom_obj)
object_files3= $(task_gate32_obj) $(trap_gate32_obj) $(intt_gate32_obj) $(tss32d_obj) $(ldtd_obj) $(gdt_obj) $(ldt_obj) $(idt_obj) $(dtables_obj)
object_files= $(object_files1) $(object_files2) $(object_files3)
#==================== object files locations ====================













#============================compile====================================
calls1= selector.o io.o pde.o pte.o pgdr.o pgcr.o rcontrol.o rsegment.o rsystem.o debug.o eflags.o farcalls.o ecode.o interrupt.o  atom.o
calls2= descriptors.o segment.o data.o code.o task_gate32.o trap_gate32.o intt_gate32.o call_gate32.o ldtd.o tss32d.o dtables.o idt.o ldt.o gdt.o
calls= $(calls1) $(calls2)
library.o: $(calls)
	$(ld) $(ld_flags) $(object_files) -o $(library_file);echo "\n";

#selector
selector.c.o: $(source_path)/selector/selector.c
	$(cc) $(cc_flags) -c $(source_path)/selector/selector.c -o $(selector_c_obj);echo "\n";
selector.o: selector.c.o
#io
io.c.o: $(source_path)/io/io.c 
	$(cc) $(cc_flags) -c $(source_path)/io/io.c -o $(io_c_obj); echo "\n";
io.asm.o: $(source_path)/io/io.asm
	$(asm) $(asm_flags) $(source_path)/io/io.asm -o $(io_asm_obj); echo "\n";
io.o: io.asm.o io.c.o 
#pde
pde.c.o: $(source_path)/paging/pde.c
	$(cc) $(cc_flags) -c $(source_path)/paging/pde.c -o $(pde_c_obj); echo "\n";
pde.o: pde.c.o
#pte
pte.c.o: $(source_path)/paging/pte.c
	$(cc) $(cc_flags) -c $(source_path)/paging/pte.c -o $(pte_c_obj); echo "\n";
pte.o: pte.c.o
#pgdr
pgdr.c.o: $(source_path)/paging/pgdr.c
	$(cc) $(cc_flags) -c $(source_path)/paging/pgdr.c -o $(pgdr_c_obj); echo "\n";
pgdr.o: pgdr.c.o
#pgcr
pgcr.c.o: $(source_path)/paging/pgcr.c
	$(cc) $(cc_flags) -c $(source_path)/paging/pgcr.c -o $(pgcr_c_obj); echo "\n";
pgcr.o: pgcr.c.o
#control registers
rcontrol.c.o: $(source_path)/registers/control/control.c 
	$(cc) $(cc_flags) -c $(source_path)/registers/control/control.c -o $(rcontrol_c_obj); echo "\n";
rcontrol.asm.o: $(source_path)/registers/control/control.asm
	$(asm) $(asm_flags) $(source_path)/registers/control/control.asm -o $(rcontrol_asm_obj); echo "\n";
rcontrol.o: rcontrol.asm.o rcontrol.c.o
#system registers
rsystem.c.o: $(source_path)/registers/system/system.c 
	$(cc) $(cc_flags) -c $(source_path)/registers/system/system.c -o $(rsystem_c_obj); echo "\n";
rsystem.asm.o: $(source_path)/registers/system/system.asm
	$(asm) $(asm_flags) $(source_path)/registers/system/system.asm -o $(rsystem_asm_obj); echo "\n";
rsystem.o: rsystem.asm.o rsystem.c.o
#segment registers
rsegment.c.o: $(source_path)/registers/segment/segment.c 
	$(cc) $(cc_flags) -c $(source_path)/registers/segment/segment.c -o $(rsegment_c_obj); echo "\n";
rsegment.asm.o: $(source_path)/registers/segment/segment.asm
	$(asm) $(asm_flags) $(source_path)/registers/segment/segment.asm -o $(rsegment_asm_obj); echo "\n";
rsegment.o: rsegment.asm.o rsegment.c.o
#debug registers
debug.c.o: $(source_path)/registers/debug/debug.c 
	$(cc) $(cc_flags) -c $(source_path)/registers/debug/debug.c -o $(debug_c_obj); echo "\n";
debug.asm.o: $(source_path)/registers/debug/debug.asm
	$(asm) $(asm_flags) $(source_path)/registers/debug/debug.asm -o $(debug_asm_obj); echo "\n";
debug.o: debug.asm.o debug.c.o
#eflags registers
eflags.c.o: $(source_path)/registers/eflags/eflags.c 
	$(cc) $(cc_flags) -c $(source_path)/registers/eflags/eflags.c -o $(eflags_c_obj); echo "\n";
eflags.asm.o: $(source_path)/registers/eflags/eflags.asm
	$(asm) $(asm_flags) $(source_path)/registers/eflags/eflags.asm -o $(eflags_asm_obj); echo "\n";
eflags.o: eflags.asm.o eflags.c.o
#interrupt
interrupt.asm.o: $(source_path)/interrupt/interrupt.asm
	$(asm) $(asm_flags) $(source_path)/interrupt/interrupt.asm -o $(interrupt_asm_obj); echo "\n";
interrupt.o: interrupt.asm.o
#ecode
ecode.c.o: $(source_path)/ecode/ecode.c
	$(cc) $(cc_flags) -c $(source_path)/ecode/ecode.c -o $(ecode_c_obj); echo "\n";
ecode.asm.o: $(source_path)/ecode/ecode.asm
	$(asm) $(asm_flags) $(source_path)/ecode/ecode.asm -o $(ecode_asm_obj); echo "\n";
ecode.o: ecode.asm.o ecode.c.o
#farcalls
farcalls.c.o: $(source_path)/farcalls/farcalls.c
	$(cc) $(cc_flags) -c $(source_path)/farcalls/farcalls.c -o $(farcalls_c_obj); echo "\n";
farcalls.asm.o: $(source_path)/farcalls/farcalls.asm
	$(asm) $(asm_flags) $(source_path)/farcalls/farcalls.asm -o $(farcalls_asm_obj); echo "\n";
farcalls.o: farcalls.asm.o farcalls.c.o
#descriptors
descriptors.c.o: $(source_path)/descriptors/descriptors.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/descriptors.c -o $(descriptors_obj); echo "\n";
descriptors.o: descriptors.c.o
#segment
segment.c.o: $(source_path)/descriptors/segment/segment.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/segment/segment.c -o $(segment_obj); echo "\n";
segment.o: segment.c.o
#data
data.c.o: $(source_path)/descriptors/segment/data.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/segment/data.c -o $(data_obj); echo "\n";
data.o: data.c.o
#code
code.c.o: $(source_path)/descriptors/segment/code.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/segment/code.c -o $(code_obj); echo "\n";
code.o: code.c.o
#call_gate32
call_gate32.c.o: $(source_path)/descriptors/system/call_gate32.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/system/call_gate32.c -o $(call_gate32_obj); echo "\n";
call_gate32.o: call_gate32.c.o
#trap_gate32
trap_gate32.c.o: $(source_path)/descriptors/system/trap_gate32.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/system/trap_gate32.c -o $(trap_gate32_obj); echo "\n";
trap_gate32.o: trap_gate32.c.o
#task_gate32
task_gate32.c.o: $(source_path)/descriptors/system/task_gate32.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/system/task_gate32.c -o $(task_gate32_obj); echo "\n";
task_gate32.o: task_gate32.c.o
#intt_gate32
intt_gate32.c.o: $(source_path)/descriptors/system/intt_gate32.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/system/intt_gate32.c -o $(intt_gate32_obj); echo "\n";
intt_gate32.o: intt_gate32.c.o
#tss32d
tss32d.c.o: $(source_path)/descriptors/system/tss32d.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/system/tss32d.c -o $(tss32d_obj); echo "\n";
tss32d.o: tss32d.c.o
#ldtd
ldtd.c.o: $(source_path)/descriptors/system/ldtd.c 
	$(cc) $(cc_flags) -c $(source_path)/descriptors/system/ldtd.c -o $(ldtd_obj); echo "\n";
ldtd.o: ldtd.c.o
#dtables
dtables.c.o: $(source_path)/dtables/dtables.c
	$(cc) $(cc_flags) -c $(source_path)/dtables/dtables.c -o $(dtables_obj); echo "\n";
dtables.o: dtables.c.o
#idt
idt.c.o: $(source_path)/dtables/idt/idt.c
	$(cc) $(cc_flags) -c $(source_path)/dtables/idt/idt.c -o $(idt_c_obj); echo "\n";
idt.asm.o: $(source_path)/dtables/idt/idt.asm
	$(asm) $(asm_flags) $(source_path)/dtables/idt/idt.asm -o $(idt_asm_obj); echo "\n";
idt.o: idt.c.o idt.asm.o 
#ldt
ldt.c.o: $(source_path)/dtables/ldt/ldt.c
	$(cc) $(cc_flags) -c $(source_path)/dtables/ldt/ldt.c -o $(ldt_c_obj); echo "\n";
ldt.o: ldt.c.o 
#gdt
gdt.c.o: $(source_path)/dtables/gdt/gdt.c
	$(cc) $(cc_flags) -c $(source_path)/dtables/gdt/gdt.c -o $(gdt_c_obj); echo "\n";
gdt.asm.o: $(source_path)/dtables/gdt/gdt.asm
	$(asm) $(asm_flags) $(source_path)/dtables/gdt/gdt.asm -o $(gdt_asm_obj); echo "\n";
gdt.o: gdt.c.o gdt.asm.o 
#atom
atom.asm.o: $(source_path)/atom/atom.asm
	$(asm) $(asm_flags) $(source_path)/atom/atom.asm -o $(atom_asm_obj); echo "\n";
atom.o: atom.asm.o
#============================compile====================================


#========================================== CLEAN ALL ======================================
clean:	
	rm -rf $(object_files)
	rm -rf $(library_file)