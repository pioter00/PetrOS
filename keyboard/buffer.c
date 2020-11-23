#include "../include/keyboard.h"
#include "../include/macros.h"
#include "../include/terminal.h"
#include "../include/isr.h"
#include "../include/irq.h"
#include "../include/std.h"
#include <stdint.h>

#define buf keyboard.buffer

void buf_putch(char c) {
	if (c == '\t') {
        for (int i = 0; i < 4; i++) 
            buf_putch(' ');
	}
    else if (c == '\b') {
        if (buf.index > 0) {
            buf.index--;
            buf_putch(0);
            buf.index--;
        }
	}
	else {
        buf.txt[buf.index++] = c;
        if (buf.index > buf.size) buf.size = buf.index;
    }
}