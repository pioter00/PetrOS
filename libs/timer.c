#include "../include/timer.h"
#include "../include/terminal.h"
#include "../include/macros.h"
#include "../include/threads.h"
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



void update_time(){
    int temp_y = main_terminal.row;
    int temp_x = main_terminal.column;
    main_terminal.row = 0;
    main_terminal.column = 27;
    datetime_print();
    main_terminal.row = temp_y;
    main_terminal.column = temp_x;
}

volatile unsigned int timer_ticks = 0;

void timer_handler(struct regs *r)
{
    timer_ticks++;
    // if (timer_ticks > 1) scheluder();
    if (timer_ticks % FREQ == 0){
        if (++datetime.seconds > 59){
            datetime.seconds = 0;
            if (++datetime.minutes > 59){
                datetime.minutes = 0;
                if (++datetime.hours > 23){
                    datetime.hours = 0;
                    if (++datetime.day > 31){
                        datetime.day = 1;
                        if (++datetime.month > 12){
                            datetime.month = 1;
                            datetime.year++;
                        }
                    }
                }
            }
        }
        update_time();
    }
}
void timer_install()
{
    set_frequency(FREQ);
    irq_install_handler(0, timer_handler);
}

void sleep(int ms){
	unsigned long sleep_ticks = timer_ticks + ms/(1000 / FREQ);
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

void printint_at_date(int a)
{
	if (a == 0)
	{
		insert_at('0', main_terminal.column++, main_terminal.row);
		return;
	}
	int size = num_len(abs(a)), i;
	char x;
	if (a > 0)
	{
		for(i=size-1;i>=0;i--)
		{
			x = a / (int)power10(i) % 10 + '0';
			insert_at(x, main_terminal.column++, main_terminal.row);
		}
	}
	else
	{
		a = abs(a);
		for(i=size;i>=0;i--)
		{
			if (i == size) putch('-');
			else
			{
				x = a / (int)power10(i) % 10 + '0';
				insert_at(x, main_terminal.column++, main_terminal.row);

			}
		}
		size++;
	}
}
void printstring_at_date(char *txt)
{
	for(unsigned int i = 0; i < strlen(txt); i++){
		insert_at(*(txt + i), main_terminal.column++, main_terminal.row);
	}
}
void datetime_print(){
    // print("%d/0%d/%d  %d:0%d:0%d", datetime.day, datetime.month, datetime.year, datetime.hours, datetime.minutes, datetime.seconds);
    if (datetime.day > 9) printint_at_date(datetime.day);
    else {
        printint_at_date(0);
        printint_at_date(datetime.day);
    }
    printstring_at_date("/");
    if (datetime.month > 9) printint_at_date(datetime.month);
    else {
        printint_at_date(0);
        printint_at_date(datetime.month);
    }
    printstring_at_date("/");
    printint_at_date(datetime.year);
    printstring_at_date("  ");
    if (datetime.hours > 9) printint_at_date(datetime.hours);
    else {
        printint_at_date(0);
        printint_at_date(datetime.hours);
    }
    printstring_at_date(":");
    if (datetime.minutes > 9) printint_at_date(datetime.minutes);
    else {
        printint_at_date(0);
        printint_at_date(datetime.minutes);
    }
    printstring_at_date(":");
    if (datetime.seconds > 9) printint_at_date(datetime.seconds);
    else {
        printint_at_date(0);
        printint_at_date(datetime.seconds);
    }
}