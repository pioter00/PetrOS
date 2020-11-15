#include "../include/timer.h"
#include "../include/terminal.h"
#include "../include/std.h"

volatile unsigned int timer_ticks = 0;

void sleep(int ms){
	timer_ticks = 0;
	for(int i = 0; timer_ticks < ms*1940; i++)
		++timer_ticks;
	timer_ticks = 0;
}