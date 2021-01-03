#ifndef CMOS_H
#define CMOS_H

#include <stdint.h>
#include "isr.h"

#define CMOS_SECONDS 0x00
#define CMOS_MINUTES 0x02
#define CMOS_HOURS 0x04
#define CMOS_WEEKDAY 0x06
#define CMOS_DAY 0x07
#define CMOS_MONTH 0x08
#define CMOS_YEAR 0x09
#define CMOS_CENTURY 0x32
#define CMOS_REG_B 0x0B

uint8_t cmos_read(uint8_t port);
uint8_t convert_from_binary(uint8_t value);
uint8_t convert_to_binary(uint8_t value);
void read_full_date();
void write_full_date(uint8_t day, uint8_t month, uint8_t year, uint8_t hour, uint8_t minutes, uint8_t seconds);
void cmos_write(uint8_t value, uint8_t port);

#endif