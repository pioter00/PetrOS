#include <stddef.h>
#include <stdint.h>
#include "include/gdt.h"
#include "include/idt.h"
#include "include/isr.h"
#include "include/irq.h"
#include "include/keyboard.h"
#include "include/std.h"
#include "include/timer.h"
#include "include/threads.h"
#include "include/terminal.h"
#include "include/macros.h"
#include "include/commands.h"

void main() 
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	datetime_install();
	timer_install();
	keyboard_install();
	threads_install();
	terminal_initialize();
}