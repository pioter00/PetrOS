#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "std.h"
#include "../terminal/terminal.h"

void putchar(char c) 
{

	if (c == '\n') {
		main_terminal.row++;
		main_terminal.column = -1;
	}
	else if (c == '\t') {
		main_terminal.column += 4;
	}
	else insert_at(c, main_terminal.color, main_terminal.column, main_terminal.row);
	if (++ main_terminal.column == WIDTH_T) {
		main_terminal.column = 0;
		if (++main_terminal.row == HEIGHT_T)
			main_terminal.row = 0;
	}
}
unsigned int strlen(char *txt){
	unsigned int i = 0;
	while (*txt++){
		i++;
	}
	return i;
}
void printstring(char *txt)
{
	for(unsigned int i = 0; i < strlen(txt); i++){
		putchar(*(txt + i));
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
    putchar('0');
    return 1;
  }
  int size = num_len(abs(a)), i;
  char x;
  if (a > 0)
  {
    for(i=size-1;i>=0;i--)
    {
      x = a / (int)power10(i) % 10 + '0';
      putchar(x);
    }
  }
  else
  {
    a = abs(a);
    for(i=size;i>=0;i--)
    {
      if (i == size) putchar('-');
      else
      {
        x = a / (int)power10(i) % 10 + '0';
        putchar(x);
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
      putchar(x);
      if (i == 5) putchar('.');
    }
    size++;
  }
  else
  {
    b = llabs(b);
    for(i=size;i>=0;i--)
    {
      if (i == size) putchar('-');
      else
      {
        x = (long)b / (long)power10(i) % (long)10 + '0';
        putchar(x);
        if (i == 5) putchar('.');
      }
    }
    size += 2;
  }
  return size;
}
void printf(char *output, ...)
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
        putchar(*(output + i));
        i++;
      }
    }
    else {
      putchar(*(output + i));
      i++;
    }
  }
  va_end(tab);
}
void sleep(unsigned int miliseconds){

}