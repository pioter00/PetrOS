#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "isr.h"
#include <stdint.h>

void keyboard_handler(struct regs *r);
void keyboard_install();

#define KBD_BUF 1024

struct keyboard_t {
	uint8_t caps_flag;
	uint8_t shift_flag;
	uint8_t ctrl_flag;
	uint8_t alt_flag;
	uint8_t read_flag;
	struct 
	{
		char *txt;
		uint32_t index;
		uint32_t size;
	} buffer;
} keyboard;

void kbd_putchar(char c);
void kbd_set(uint8_t code);
void buf_putch(char c);



#endif