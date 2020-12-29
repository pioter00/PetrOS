#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/threads.h"
#include "../include/timer.h"
#include "../include/terminal.h"
#include "../include/irq.h"
#include "../include/std.h"
#include <stdint.h>

void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(struct regs *r)) {
    irq_routines[irq] = handler;
}
void irq_uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}


void irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}
uint32_t stack1[THREAD_STACK_SIZE];
uint32_t stack2[THREAD_STACK_SIZE];
void task1(){
	int timer_tick1 = 0;
	while (1){
		mutex_lock();
		int temp_y = main_terminal.row;
		int temp_x = main_terminal.column;
		main_terminal.row = 15;
   		main_terminal.column = 1;
		printint_at_date(timer_tick1++);
		main_terminal.row = temp_y;
		main_terminal.column = temp_x;
		mutex_relase();
		sleep(100);
		} 
}
void timer(){
	while(1){
		task_schedule(&tim, &t1);
		task_schedule(&t1, &t2);
		task_schedule(&t2, &tim);
	}
}
void task2(){
	int timer_tick2 = 0;
	while (1){
		mutex_lock();
		int temp_y = main_terminal.row;
		int temp_x = main_terminal.column;
		main_terminal.row = 15;
   		main_terminal.column = 14;
		printint_at_date(timer_tick2++);
		main_terminal.row = temp_y;
		main_terminal.column = temp_x;
		mutex_relase();
		sleep(500);
	}
	
}
void irq_install()
{
    create_thread(&t1, stack1, (uint32_t)task1);
	create_thread(&t2, stack2, (uint32_t)task2);
    irq_remap();
    idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);

    idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}
volatile unsigned int xd = 0;
void irq_handler(struct regs *r) {
    void (*handler)(struct regs *r);
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }
    if (r->int_no >= 40)
    {
        outportb(0xA0, 0x20);
    }
    outportb(0x20, 0x20);
    xd++;
    if (xd > 11 && xd % 3 == 0){
        task_schedule(&t1, &tim);
    }
    else if (xd > 11 && xd % 3 == 1){
        task_schedule(&tim, &t2);  
    } 
	else if (xd > 11 && xd % 3 == 2){
        task_schedule(&t2, &t1);
    } 
}