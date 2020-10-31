[BITS 32] 
[SECTION .text] 
EXTERN code,bss,end 
mboot: 
dd 0x1BADB002 ; Sygnatura 
dd 0x10001 ; Flagi dla bootloadera 
dd -(0x1BADB002+0x10001) ; suma kontrolna nagłówka 
dd mboot ; Pozycja nagłówka w pliku 
dd code 
dd bss 
dd end 
dd start 

GLOBAL start 
start: 
cli 
mov esp,kstack+4096 
mov ax,0x10 
mov ds,ax 
mov es,ax 
mov fs,ax 
mov gs,ax 
lgdt [gdt_descr] 
jmp .1 
.1: 
extern reroute_irqs 
call reroute_irqs 
push dword 0 
push dword 0 
push dword 0 
push dword L6 
EXTERN start_kernel 
push dword start_kernel 
ret 
L6: 
jmp L6 

[SECTION .bss] 
kstack: resd 2048 

[SECTION .data] 
gdt_descr: 
dw 256*8-1 
dd gdt 

GLOBAL gdt 
gdt: 
dd 0,0 
dd 0x0000FFFF,0x00CF9A00 
dd 0x0000FFFF,0x00CF9200 
dd 0,0 
times 254 dd 0,0