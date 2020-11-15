#include "timer.h"
#include "../terminal/terminal.h"
#include "std.h"
#include "asm.h"
void timer_install(int hz) {
	unsigned int divisor = 1193180/hz;
	outb(0x36, 0x43);
	outb(divisor&0xff, 0x40);
	outb(divisor>>8, 0x40);
	outb(inb(0x21)&0xfe, 0x21);
}

volatile unsigned int timer_ticks = 0;

void sleep(int ms){
	timer_install(1);
	timer_ticks = 0;
	for(int i = 0; timer_ticks < ms*1940; i++)
		++timer_ticks;
	timer_ticks = 0;
}