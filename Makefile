.SUFFIXES: .asm; 
OUTFILE := kernel.bin 
OBJS := start.o irqroute.o kernel.o libs/std.o terminal/terminal.o 
CFLAGS := -O2 -fomit-frame-pointer -nostdinc -fno-builtin -m32 -fno-pie

comp:
	nasm irqroute.asm -f elf32 -o irqroute.o
	nasm start.asm -f elf32 -o start.o 
	gcc libs/std.c -c -o libs/std.o -m32 -O2 -fomit-frame-pointer -fno-pie
	gcc terminal/terminal.c -c -o terminal/terminal.o -m32 -O2 -fomit-frame-pointer -fno-pie
	gcc kernel.c -m32 -O2 -fno-pie -fno-builtin -c -o kernel.o
	ld -Tlinker.ld -o $(OUTFILE) $(OBJS)
	cp kernel.bin isodir/boot/kernel.bin
	grub-mkrescue -o myos.iso isodir

.asm.o: 
	nasm $*.asm -f elf32 -o $*.o