#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "isr.h"
#include <stdint.h>

void keyboard_handler(struct regs *r);
void keyboard_install();

struct keyboard_t {
	uint8_t caps_flag;
	uint8_t shift_flag;
	uint8_t ctrl_flag;
	uint8_t alt_flag;
};

struct keyboard_t keyboard;

void kbd_putchar(char c);
void kbd_set(uint8_t code);

#endif