#include "../include/timer.h"
#include "../include/terminal.h"
#include "../include/std.h"
#include "../include/irq.h"
#include "../include/isr.h"

void set_frequency(int hz)
{
    int divisor = 1193180 / hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

volatile unsigned int timer_ticks = 0;

void update_time(){
    int temp_y = main_terminal.row;
    int temp_x = main_terminal.column;
    main_terminal.row = 0;
    main_terminal.column = 27;
    datetime_print();
    main_terminal.row = temp_y;
    main_terminal.column = temp_x;
    move_csr();
}

void timer_handler(struct regs *r)
{
    timer_ticks++;
    if (timer_ticks % 100 == 0){
        datetime.seconds++;
        update_time();
    }
}
void timer_install()
{
    set_frequency(100);
    irq_install_handler(0, timer_handler);
}

void sleep(int ms){
	unsigned long sleep_ticks = timer_ticks + ms*10;
    while (timer_ticks < sleep_ticks);
}
void datetime_install() {
    datetime.seconds = 0;
    datetime.minutes = 0;
    datetime.hours = 0;
    datetime.day = 1;
    datetime.month = 1;
    datetime.year = 2000;
}
void datetime_print(){
    print("%d/0%d/%d  %d:0%d:0%d", datetime.day, datetime.month, datetime.year, datetime.hours, datetime.minutes, datetime.seconds);
}