#include "../include/timer.h"
#include "../include/terminal.h"
#include "../include/std.h"

void timer_install(int hz)
{
    int divisor = 1193180 / hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

volatile unsigned int timer_ticks = 0;

void sleep(int ms){
	timer_ticks = 0;
	for(int i = 0; timer_ticks < ms*1940; i++)
		++timer_ticks;
	timer_ticks = 0;
}