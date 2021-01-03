#include "../include/timer.h"
#include "../include/cmos.h"
#include "../include/terminal.h"
#include "../include/macros.h"
#include "../include/threads.h"
#include "../include/std.h"
#include "../include/irq.h"
#include "../include/isr.h"


uint8_t cmos_read(uint8_t port)
{
    uint8_t byte1 = 1 << 7 | port;
    outportb(0x70, byte1);
    uint8_t value = inportb(0x71);
    return value;
}
char *weekdays[] = {"Sun", "Mon", "Tue", "Wen", "Thu", "Fri", "Sat"};
void read_full_date(){
    datetime.seconds = convert_from_binary(cmos_read(CMOS_SECONDS));
    datetime.minutes = convert_from_binary(cmos_read(CMOS_MINUTES));
    datetime.hours = convert_from_binary(cmos_read(CMOS_HOURS));
    mem_cpy(datetime.weekday, weekdays[convert_from_binary(cmos_read(CMOS_WEEKDAY)) - 1], 4);
    datetime.day = convert_from_binary(cmos_read(CMOS_DAY));
    datetime.month = convert_from_binary(cmos_read(CMOS_MONTH));
    datetime.year = convert_from_binary(cmos_read(CMOS_CENTURY)) * 100 + convert_from_binary(cmos_read(CMOS_YEAR));
}
uint8_t convert_from_binary(uint8_t value){
    return (value & 0x0F) + ((value / 16) * 10);
}
void cmos_write(uint8_t value, uint8_t port){
    uint8_t byte1 = 0 << 7 | port;
    outportb(0x70, byte1);
    outportb(0x71, value);
}
uint8_t convert_to_binary(uint8_t value){
    return value + ((value - value % 10) / 10) * 6;
}
void write_full_date(uint8_t day, uint8_t month, uint8_t year, uint8_t hour, uint8_t minutes, uint8_t seconds){
    cmos_write(convert_to_binary(day), CMOS_DAY);
    cmos_write(convert_to_binary(month), CMOS_MONTH);
    cmos_write(convert_to_binary(year), CMOS_YEAR);
    cmos_write(convert_to_binary(hour), CMOS_HOURS);
    cmos_write(convert_to_binary(minutes), CMOS_MINUTES);
    cmos_write(convert_to_binary(seconds), CMOS_SECONDS);
}