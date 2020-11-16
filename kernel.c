#include <stddef.h>
#include <stdint.h>
#include "include/gdt.h"
#include "include/idt.h"
#include "include/isr.h"
#include "include/irq.h"
#include "include/keyboard.h"
#include "include/std.h"
#include "include/timer.h"
#include "include/terminal.h"


char *user = "pjoter";

unsigned char kbdxd[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void main() 
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	terminal_initialize();
	// keyboard_install();
	print("\tPetrOS 0.01\n\n");
	set_fn_col(DARK_GREY);
	for(int i = 0; i < WIDTH_T; i++){
		print("=");
	}
	set_fn_col(GREEN);
	print("\n");
	print("        ||\\\\\\\\                                  ///|||\\\\\\    ////|\\\\\\\n");
	print("        ||   \\\\             ||                 ||       ||  ||      \\\\\n");
	print("        ||    ||            ||                 ||       ||  ||\n");
	print("        ||    //          \\\\\\\\\\\\               ||       ||   \\\\\n");
	print("        ||/////    ////\\\\   ||      ///|||\\    ||       ||     \\\\\\\\\n");
	print("        ||        ||    \\\\  ||     //  ||  \\\\  ||       ||          \\\\\n");
	print("        ||        ||||||||  ||         ||      ||       ||           ||\n");
	print("        ||        ||        ||         ||      ||       ||   \\      ||\n");
	print("        ||         //////    \\\\\\\\      ||       |\\\\\\||///     \\\\|/////\n\n");
	set_fn_col(DARK_GREY);
	for(int i = 0; i < WIDTH_T; i++){
		print("=");
	}
	print("\n");

	set_fn_col(GREEN);
	print("%s", user);
	set_fn_col(LIGHT_GREY);
	print("$");
	set_fn_col(BLUE);
	print("home");
	set_fn_col(LIGHT_GREY);
	print("> \n");
	unsigned char prev = 0;
	while (1)
	{
		unsigned char scancode = inportb(0x60);
		if (!(scancode & 0x80) && prev != scancode) putch(kbdxd[scancode]);
		prev = scancode;
	}

	
}