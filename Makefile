OUTFILE := kernel.bin 
OBJS := start.o kernel.o libs/std.o terminal/terminal.o libs/timer.o libs/gdt.o libs/idt.o libs/isr.o libs/irq.o libs/kbd.o
CFLAGS := -O2 -fomit-frame-pointer -fno-builtin -m32 -fno-pie

full:
	make comp
	make clean
	make run

comp:
	nasm start.asm -f elf32 -o start.o 
	gcc libs/std.c -c -o libs/std.o $(CFLAGS)
	gcc libs/gdt.c -c -o libs/gdt.o $(CFLAGS)
	gcc libs/idt.c -c -o libs/idt.o $(CFLAGS)
	gcc libs/isr.c -c -o libs/isr.o $(CFLAGS)
	gcc libs/irq.c -c -o libs/irq.o $(CFLAGS)
	gcc libs/kbd.c -c -o libs/kbd.o $(CFLAGS)
	gcc terminal/terminal.c -c -o terminal/terminal.o $(CFLAGS)
	gcc libs/timer.c -c -o libs/timer.o $(CFLAGS)
	gcc kernel.c -m32 -O2 -fno-pie -fno-builtin -c -o kernel.o
	ld -Tlinker.ld -o $(OUTFILE) $(OBJS)
	cp $(OUTFILE) isodir/boot/kernel.bin
	grub-mkrescue -o PetrOS.iso isodir

run:	
	qemu-system-i386 -cdrom PetrOS.iso

clean:
	find . -type f -name '*.o' -delete