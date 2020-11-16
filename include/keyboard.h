#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "isr.h"

void keyboard_handler(struct regs *r);
void keyboard_install();

#endif