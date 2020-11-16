OUTFILE := kernel.bin 
OBJS := start.o kernel.o libs/std.o terminal/terminal.o libs/timer.o libs/gdt.o libs/idt.o
CFLAGS := -O2 -fomit-frame-pointer -nostdinc -fno-builtin -m32 -fno-pie

comp:
	nasm start.asm -f elf32 -o start.o 
	gcc libs/std.c -c -o libs/std.o -m32 -O2 -fomit-frame-pointer -fno-pie
	gcc libs/gdt.c -c -o libs/gdt.o -m32 -O2 -fomit-frame-pointer -fno-pie
	gcc libs/idt.c -c -o libs/idt.o -m32 -O2 -fomit-frame-pointer -fno-pie
	gcc terminal/terminal.c -c -o terminal/terminal.o -m32 -O2 -fomit-frame-pointer -fno-pie
	gcc libs/timer.c -c -o libs/timer.o -m32 -O2 -fomit-frame-pointer -fno-pie
	gcc kernel.c -m32 -O2 -fno-pie -fno-builtin -c -o kernel.o
	ld -Tlinker.ld -o $(OUTFILE) $(OBJS)
	cp kernel.bin isodir/boot/kernel.bin
	grub-mkrescue -o PetrOS.iso isodir
	qemu-system-i386 -cdrom PetrOS.iso

clean:
	find . -type f -name '*.o' -delete