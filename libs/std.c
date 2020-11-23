#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "../include/std.h"
#include "../include/irq.h"
#include "../include/isr.h"
#include "../include/terminal.h"
#include "../include/keyboard.h"

unsigned char inportb (unsigned short _port)
{
		unsigned char rv;
		__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
		return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
		__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void putch(char c) 
{

	if (c == '\n') {
		main_terminal.row++;
		main_terminal.column = 0;
	}
	else if (c == '\t') {
		main_terminal.column += 4;
	}
	else if (c == '\b' && main_terminal.column == 0) {
		main_terminal.row--;
		main_terminal.column = 79;
		insert_at(' ', 79, main_terminal.row);
	}
	else if (c == '\b' && main_terminal.column > 0) {
		insert_at(' ', --main_terminal.column, main_terminal.row);
		set_fn_col(LIGHT_GREY);
	}
	else if (c == 0){
		print("%c", '0');
		insert_at(0, main_terminal.column, main_terminal.row);
	}
	else {
		insert_at(c, main_terminal.column, main_terminal.row);
		main_terminal.column++;
	} 
	if (main_terminal.column == WIDTH_T){
		main_terminal.column = 0;
		main_terminal.row++;
	} 
	if (main_terminal.row == HEIGHT_T){
		scroll();
		main_terminal.row = HEIGHT_T - 1;
		for (int i = 0; i < WIDTH_T; i++) {
			insert_at(' ', main_terminal.column + i, main_terminal.row);
		}
	}
	move_csr(); 
}

void move_csr() {
	unsigned temp = main_terminal.row * 80 + main_terminal.column;
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}

unsigned int strlen(char *txt){
	unsigned int i = 0;
	while (*txt++) i++;
	return i;
}
void *mem_set(void *dest, char c, size_t size)
{
		uint8_t *temp = (uint8_t *)dest;
		while(size--) 
			*temp++ = c;
		return dest;
}
void printstring(char *txt)
{
	for(unsigned int i = 0; i < strlen(txt); i++){
		putch(*(txt + i));
	}
}

long long power10(int base)
{
	int i;
	long long a = 1;
	for(i=0;i<base;i++)
	{
		a *= 10;
	}
	return a;
}
int abs(int a){
	if (a >= 0) return a;
	else return -a;  
}
long long llabs(long long a){
	if (a >= 0) return a;
	else return -a;  
}

unsigned int num_len(long long num){
	if (!num) return 1;
	for (unsigned int i = 0; i < 15; i++) {
		if (power10(i) > num) return i;
	}
}
int printint(int a)
{
	if (a == 0)
	{
		putch('0');
		return 1;
	}
	int size = num_len(abs(a)), i;
	char x;
	if (a > 0)
	{
		for(i=size-1;i>=0;i--)
		{
			x = a / (int)power10(i) % 10 + '0';
			putch(x);
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
				putch(x);
			}
		}
		size++;
	}
	return size;
}
int printdouble(double a)
{
	if (a == 0)
	{
		printstring("0.00000");
		return 7;
	}
	int size = num_len(abs(a)) + 5, i;

	long long b = (long long)(a * 100000);
	char x;
	if (a > 0)
	{
		for(i=size-1;i>=0;i--)
		{
			x = (long)b / (long)power10(i) % (long)10 + '0';
			putch(x);
			if (i == 5) putch('.');
		}
		size++;
	}
	else
	{
		b = llabs(b);
		for(i=size;i>=0;i--)
		{
			if (i == size) putch('-');
			else
			{
				x = (long)b / (long)power10(i) % (long)10 + '0';
				putch(x);
				if (i == 5) putch('.');
			}
		}
		size += 2;
	}
	return size;
}
void print(char *output, ...)
{
	int counter = 0, i = 0, size = strlen(output);
	va_list tab;
	va_start(tab, output);
	char *s;
	int a = 0;
	double b = 0;
	for (i=0;i<size;)
	{
		if(*(output + i) == '%' && i < size - 1)
		{
			if(*(output + i + 1) == 's')
			{
				s = va_arg(tab, char*);
				printstring(s);
				i += 2;
			}
			else if(*(output + i + 1) == 'c')
			{
				a = va_arg(tab, int);
				putch(a);
				i += 2;
			}
			else if(*(output + i + 1) == 'd')
			{
				a = va_arg(tab, int);
				printint(a);
				i += 2;
			}
			else if(*(output + i + 1) == 'f')
			{
				b = va_arg(tab, double);
				printdouble(b);
				i += 2;
			}
			else {
				putch(*(output + i));
				i++;
			}
		}
		else {
			putch(*(output + i));
			i++;
		}
	}
	va_end(tab);
}

char buf_getch() {
	char x = keyboard.buffer.txt[0];
	for (int i = 0; i < keyboard.buffer.size; i++){
		keyboard.buffer.txt[i] = keyboard.buffer.txt[i + 1];
	}
	keyboard.buffer.size--;
	keyboard.buffer.index--;
	return x;
}
void getstr(char * str) {
	outportb(0x60, 0);
	while (inportb(0x60) != 28);
	// print("%s\n", keyboard.buffer.txt);
	for (int i = 0; ; i++)
	{
		char c = buf_getch();
		if (c != '\n' && c != 0 && c != ' ') *(str + i) = c;
		else {
			*(str + i) = '\0';
			break;
		}
	}	
}
void getstrn(char * str, size_t n){
	outportb(0x60, 0);
	while (inportb(0x60) != 28);
	int i;
	for (i = 0; i < n; i++)
	{
		char c = buf_getch();
		if (c != '\n' && c != 0) *(str + i) = c;
		else {
			*(str + i) = '\0';
			break;
		}
	}
	if (i == n && n > 1) *(str + i) = '\0';
}
char c = 0;
char getch(){
	if (keyboard.buffer.index == 0) getstrn(&c, 1);
	else c = buf_getch();
	return c;
}
int getint(int *var)
{
  *var = 0;
  int first = 0, sign = 1, flag = 1, res = 1;
  char c = getch();
  while (1)
  {
    if(c == '-' && first == 0) sign = -1;
    else
    {
      if(isdigit(c) != 0 && flag == 1)
      {
        *var += c - '0';
      }
      if(isdigit(c) == 0 && c != '-' && flag == 1)
      {
        if (first == 0) res = 0;
        flag = 0;
      }
    }
    first = 1;
    c = getch();
    if (isspace(c)) break;
    else if (isdigit(c) != 0 && flag == 1) *var *= 10;
  }
  *var *= sign;
  return res;
}
int getdouble(double *var)
{
  *var = 0;
  int flag = 1, first = 0, sign = 1, point = 0, pos = 0, res = 1;
  char c = getch();
  while (1)
  {
    if(c == '-' && first == 0) sign = -1;
    else
    {
      if(isdigit(c) != 0 && flag == 1 && point <= 1) *var += c - '0';
      if(isdigit(c) != 0 && flag == 1 && point == 1) pos++;
      if(isdigit(c) == 0 && c == '.')
      {
        point++;
        if (point > 1) flag = 0;
      }
      if(isdigit(c) == 0 && c != '-' && c != '.' && flag == 1)
      {
        if (first == 0) res = 0;
        flag = 0;
      }
    }
    first = 1;
    c = getch();
    if (isspace(c)) break;
    else if (isdigit(c) != 0 && point <= 1 && flag == 1) *var *= 10;
  }

  *var *= sign;
  *var /= power10(pos);
  return res;
}

int scan(char *input, ...)
{
	int counter = 0, i = 0, size = strlen(input);
	va_list tab;
	va_start(tab, input);
	int *a = 0;
	double *b = 0;
	char *c;
	for (i = 0; i < size; ) {
		if(*(input + i) == '%' && i < size - 1)
		{
			if(*(input + i + 1) == 'd')
			{
				a = va_arg(tab, int*);
				counter += getint(a);
				i += 2;
			}
			else if(*(input + i + 1) == 'f')
			{
				b = va_arg(tab, double*);
				counter += getdouble(b);
				i += 2;
			}
			else if(*(input + i + 1) == 's')
			{
				c = va_arg(tab, char*);
				getstr(c);
				counter++;
				i += 2;
			}
			else i++;
		}
		else i++;
	}
	flush();
	va_end(tab);
	return counter;
}

int isdigit(char c) {
	if (c >= '0' && c <= '9') return 1;
	return 0;
}
int isspace(char c){
	if (c == ' ' || c <= '\n' || c == '\t') return 1;
	return 0;
}
void flush(){
	mem_set(keyboard.buffer.txt, 0, KBD_BUF);
	keyboard.buffer.index = 0;
	keyboard.buffer.size = 0;
}