#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

struct datetime_t
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    char weekday[4];
    uint8_t day;
    uint8_t month;
    uint16_t year;
} datetime;

#define FREQ 1000

#define DATE_X 27
#define DATE_Y 0


void datetime_install();
void datetime_print();
void update_time();
void set_frequency(int hz);
void timer_install();
void sleep(int ms);

void printint_at_date(int a);
#endif