#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

struct datetime_t
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;

    uint8_t day;
    uint8_t month;
    uint16_t year;
} datetime;

void datetime_install();
void datetime_print();
void timer_install(int hz);
void do_timer();
void sleep(int ms);
#endif