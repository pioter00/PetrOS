#include <stdint.h>
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/irq.h"
#include "../include/keyboard.h"
#include "../include/std.h"
#include "../include/timer.h"
#include "../include/threads.h"
#include "../include/terminal.h"
#include "../include/macros.h"

extern void switch_to_task(struct thread_t *next_thread);