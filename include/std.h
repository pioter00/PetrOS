#ifndef STD_H
#define STD_H

#include <stddef.h>
#include <stdint.h>

unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

unsigned int strlen(char *txt);
long long power(int base);
int abs(int a);
long long llabs(long long a);
unsigned int num_len(long long num);

void putch(char c);
void move_csr();
void print(char *output, ...);
#endif