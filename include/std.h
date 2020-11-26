#ifndef STD_H
#define STD_H

#include <stddef.h>
#include <stdint.h>

unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

unsigned int strlen(char *txt);
long long power10(int base);
int abs(int a);
long long llabs(long long a);
unsigned int num_len(long long num);
void * mem_set(void *dest, char c, size_t size);

void putch(char c);
void move_csr();
void print(char *format, ...);

char getch();
void getstr(char * str);
void getstrn(char * str, size_t n);
int scan(char *format, ...);

void flush();

int isdigit(char c);
int isspace(char c);

#endif