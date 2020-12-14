[BITS 32]
global start
start:
    mov esp, _sys_stack
    jmp stublet

ALIGN 4
mboot:
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd mboot
    dd code
    dd bss
    dd end
    dd start

stublet:
    extern main
    call main
    jmp $

global gdt_flush
extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
flush2:
    ret

global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

;  0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

;  2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

;  3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

;  4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

;  5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

;  6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6 
    jmp isr_common_stub

;  7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

;  8: Double Fault Exception
isr8:
    cli
    push byte 8
    jmp isr_common_stub

;  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

; 10: Bad TSS Exception
isr10:
    cli
    push byte 10
    jmp isr_common_stub

; 11: Segment Not Present Exception
isr11:
    cli
    push byte 11
    jmp isr_common_stub

; 12: Stack Fault Exception
isr12:
    cli
    push byte 12
    jmp isr_common_stub

; 13: General Protection Fault Exception
isr13:
    cli
    push byte 13
    jmp isr_common_stub

; 14: Page Fault Exception
isr14:
    cli
    push byte 14
    jmp isr_common_stub

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

extern fault_handler

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub

irq1:
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub

irq2:
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub

irq3:
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub

irq4:
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub

irq5:
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub

irq6:
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub

irq7:
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub

irq8:
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub

irq9:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub

irq10:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub

irq11:
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub

irq12:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub

irq13:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub

irq14:
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub

irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

extern irq_handler

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, irq_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; extern k_schedule_process

; global k_switch_process

; k_switch_process:
;     pusha
;     push ds
;     push es
;     push fs
;     push gs

;     mov eax, 0x10
;     mov ds, eax
;     mov es, eax
;     mov fs, eax
;     mov gs, eax

;     mov eax, esp

;     push eax
;     call k_schedule_process
;     mov esp, eax

;     mov al, 0x20
;     out 0x20, al

;     pop gs
;     pop fs
;     pop es
;     pop ds
;     popa

;     iret

; SECTION .text
; to co niby działało xDD =======================================================================
; global switchTask
; switchTask:
;     pusha
;     pushf
;     mov eax, cr3 ;#Push CR3
;     push eax
;     mov eax, [esp + 44] ;#The first argument, where to save
;     mov [eax + 4], ebx
;     mov [eax + 8], ebx
;     mov [eax + 12], ebx
;     mov [eax + 16], ebx
;     mov [eax + 20], ebx
;     mov ebx, [esp + 36] ;mov 36(%esp), %ebx; #EAX
;     mov ecx, [esp + 40] ;mov 40(%esp), %ecx #IP
;     mov edx, [esp + 20] ;mov 20(%esp), %edx #ESP
;     add edx, 4 ;#Remove the return value ;)
;     mov esi, [esp + 16] ;mov 16(%esp), %esi #EBP
;     mov edi, [esp + 4] ;mov 4(%esp), %edi #EFLAGS
;     mov eax, ebx ;mov %ebx, (%eax)
;     ; mov %edx, 24(%eax)
;     ; mov %esi, 28(%eax)
;     ; mov %ecx, 32(%eax)
;     ; mov %edi, 36(%eax)
;     mov [eax + 24], edx
;     mov [eax + 28], esi
;     mov [eax + 32], ecx
;     mov [eax + 36], edi
;     pop ebx ;#CR3
;     mov [eax + 40], ebx ;mov %ebx, 40(%eax)
;     push ebx ;#Goodbye again ;)
;     mov eax, [esp + 48] ;mov 48(%esp), %eax ;#Now it is the new object
;     ; mov 4(%eax), %ebx ;#EBX
;     ; mov 8(%eax), %ecx ;#ECX
;     ; mov 12(%eax), %edx ;#EDX
;     ; mov 16(%eax), %esi ;#ESI
;     ; mov 20(%eax), %edi ;#EDI
;     ; mov 28(%eax), %ebp ;#EBP
;     mov [eax + 4], ebx
;     mov [eax + 8], ecx
;     mov [eax + 12], edx
;     mov [eax + 16], esi
;     mov [eax + 20], edi
;     mov [eax + 28], ebp
;     push eax
;     mov eax, [eax + 36] ;mov 36(%eax), %eax ;#EFLAGS
;     push eax
;     popf
;     pop eax
;     mov esp, [eax + 24] ;mov 24(%eax), %esp ;#ESP
;     push eax
;     mov eax, [eax + 40] ;mov 40(%eax), %eax #CR3
;     mov cr3, eax ;mov %eax, %cr3
;     pop eax
;     push eax
;     mov eax, [eax + 32] ;mov 32(%eax), %eax #EIP
;     xchg eax, [esp];xchg (%esp), %eax #We do not have any more registers to use as tmp storage
;     mov eax, [eax] ;mov (%eax), %eax #EAX
;     ret

; to co niby działało xDD =======================================================================

; global switchTask
; switchTask:



; extern current_task
; global switch_to_task
; ; global switch_to_task
; switch_to_task:
;         ;
;         ; clear interrupts and save context.
;         ;
;         cli
;         pushad
;         ; ;
;         ; ; if no current task, just return.
;         ; ;
;         ; mov eax, [_currentTask]
;         ; cmp eax, 0
;         ; jz  interrupt_return
;         ;
;         ; save selectors.
;         ;
;         push ds
;         push es
;         push fs
;         push gs
;         ;
;         ; switch to kernel segments.
;         ;
;         mov ax, 0x10
;         mov ds, ax
;         mov es, ax
;         mov fs, ax
;         mov gs, ax
;         ;
;         ; save esp.
;         ;
;         mov eax, [current_task]
;         mov [eax], esp
;         ;
;         ; restore esp.
;         ;
;         mov eax, [current_task]
;         mov esp, [eax]
;         ;
;         ; Call tss_set_stack (kernelSS, kernelESP).
;         ; This code will be needed later for user tasks.
;         ; ;
;         ; push dword ptr [eax+8]
;         ; push dword ptr [eax+12]
;         ; call tss_set_stack
;         ; add esp, 8
;         ;
;         ; send EOI and restore context.
;         ;
;         pop gs
;         pop fs
;         pop es
;         pop ds
; extern current_task_TCB
; global switch_to_task

; switch_to_task:
 
;     ;Save previous task's state
 
;     ;Notes:
;     ;  For cdecl; EAX, ECX, and EDX are already saved by the caller and don't need to be saved again
;     ;  EIP is already saved on the stack by the caller's "CALL" instruction
;     ;  The task isn't able to change CR3 so it doesn't need to be saved
;     ;  Segment registers are constants (while running kernel code) so they don't need to be saved
 
;     push ebx
;     push esi
;     push edi
;     push ebp
 
;     mov edi,[current_task_TCB]    ;edi = address of the previous task's "thread control block"
;     ; mov [edi+TCB.ESP],esp         ;Save ESP for previous task's kernel stack in the thread's TCB
 
;     ;Load next task's state
 
;     mov esi,[esp+(4+1)*4]         ;esi = address of the next task's "thread control block" (parameter passed on stack)
;     mov [current_task_TCB],esi    ;Current task's TCB is the next task TCB
 
;     ; mov esp,[esi+TCB.ESP]         ;Load ESP for next task's kernel stack from the thread's TCB
;     ; mov eax,[esi+TCB.CR3]         ;eax = address of page directory for next task
;     ; mov ebx,[esi+TCB.ESP0]        ;ebx = address for the top of the next task's kernel stack
;     ; mov [TSS.ESP0],ebx            ;Adjust the ESP0 field in the TSS (used by CPU for for CPL=3 -> CPL=0 privilege level changes)
;     mov ecx,cr3                   ;ecx = previous task's virtual address space
 
;     cmp eax,ecx                   ;Does the virtual address space need to being changed?
;     je .doneVAS                   ; no, virtual address space is the same, so don't reload it and cause TLB flushes
;     mov cr3,eax                   ; yes, load the next task's virtual address space
; .doneVAS:
 
;     pop ebp
;     pop edi
;     pop esi
;     pop ebx
 
;     ret  



SECTION .bss
    resb 8192
_sys_stack:
