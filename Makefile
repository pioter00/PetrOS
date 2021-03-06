OUTFILE := kernel.bin 
OBJS := start.o kernel.o libs/std.o terminal/terminal.o terminal/commands.o time/timer.o time/cmos.o libs/gdt.o libs/idt.o libs/isr.o libs/irq.o libs/threads.o keyboard/kbd.o keyboard/buffer.o 
CFLAGS := -O2 -fomit-frame-pointer -fno-builtin -m32 -fno-pie -fno-stack-protector

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
	gcc libs/threads.c -c -o libs/threads.o $(CFLAGS)
	gcc keyboard/kbd.c -c -o keyboard/kbd.o $(CFLAGS)
	gcc keyboard/buffer.c -c -o keyboard/buffer.o $(CFLAGS)
	gcc terminal/terminal.c -c -o terminal/terminal.o $(CFLAGS)
	gcc terminal/commands.c -c -o terminal/commands.o $(CFLAGS)
	gcc time/timer.c -c -o time/timer.o $(CFLAGS)
	gcc time/cmos.c -c -o time/cmos.o $(CFLAGS)
	gcc kernel.c -m32 -O2 -fno-pie -fno-stack-protector -fno-builtin -c -o kernel.o
	ld -Tlinker.ld -o $(OUTFILE) $(OBJS)
	cp $(OUTFILE) isodir/boot/kernel.bin
	grub-mkrescue -o PetrOS.iso isodir

run:	
	qemu-system-i386 -cdrom PetrOS.iso

clean:
	find . -type f -name '*.o' -delete