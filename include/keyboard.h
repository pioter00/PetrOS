#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "isr.h"
#include <stdint.h>

void keyboard_handler(struct regs *r);
void keyboard_install();

#define KBD_BUF 1024
#define KBD_CAH 256
#define START_TXT 3

struct keyboard_t {
	uint8_t caps_flag;
	uint8_t shift_flag;
	uint8_t ctrl_flag;
	uint8_t alt_flag;

    char *buffer;
	uint32_t buf_index;
    char *cache;
	uint32_t cah_index;
    char last;
} keyboard;

void kbd_putchar(char c);
void kbd_set(uint8_t code);
void read_buf();


#endif