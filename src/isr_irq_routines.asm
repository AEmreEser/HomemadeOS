%ifndef _ISR_ASM_
%define _ISR_ASM_

%include "bootloader/GDT.inc"

[bits 32]
[extern int_handler] ; ignore the errors squiggles, this works for some reason

; following routines taken from (and slightly modified by me): http://www.osdever.net/bkerndev/index.php
isr_save_state: ; stack should already contain the error code pusha
    push ds
    push es
    push fs
    push gs
    pusha
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; the interrupt call should push these already
    ; mov eax, esp ; push the stack ptr
    ; push eax
isr_handler_call:
    mov eax, int_handler
    call eax ; preserves the eip register???
    add esp, 4 ; clean the argument
isr_restore_state:
    popa
    pop gs
    pop fs
    pop es
    pop ds
    add esp, 8 ; cleans error code and isr num from stack
    sti  ; re-enable interrupts
    iret ; make sure the vm flag is 0 -- ELSE RETURNS TO VIRT MODE!!!!


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

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_save_state

isr1:
    cli
    push byte 0 ; dummy error code
    push byte 1 ; interrupt number
    jmp isr_save_state

isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_save_state

isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_save_state

isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_save_state

isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_save_state

isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_save_state

isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_save_state

isr8:
    cli
    push byte 8 ; this one already pushes its own error code to the stack
    jmp isr_save_state

isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_save_state

isr10:
    cli
    push byte 10
    jmp isr_save_state

isr11:
    cli
    push byte 11
    jmp isr_save_state

isr12:
    cli
    push byte 12
    jmp isr_save_state

isr13:
    cli
    push byte 13
    jmp isr_save_state

isr14:
    cli
    push byte 14
    jmp isr_save_state

isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_save_state

isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_save_state

isr17:
    cli
    ; push byte 0 ; this one pushes an err code automatically too
    push byte 17
    jmp isr_save_state

isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_save_state

isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_save_state

isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_save_state

isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_save_state

isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_save_state

isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_save_state

isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_save_state

isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_save_state

isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_save_state

isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_save_state

isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_save_state

isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_save_state

isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_save_state

isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_save_state

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

[extern irq_handler]

irq_save_state:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
irq_handler_call:
    mov eax, irq_handler
    call eax
irq_restore_state:
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
    
irq0:
    cli
    push byte 0
    push byte 32
    jmp irq_save_state

irq1:
    cli
    push byte 0
    push byte 33
    jmp irq_save_state

irq2:
    cli
    push byte 0
    push byte 34
    jmp irq_save_state

irq3:
    cli
    push byte 0
    push byte 35
    jmp irq_save_state

irq4:
    cli
    push byte 0
    push byte 36
    jmp irq_save_state

irq5:
    cli
    push byte 0
    push byte 37
    jmp irq_save_state

irq6:
    cli
    push byte 0
    push byte 38
    jmp irq_save_state

irq7:
    cli
    push byte 0
    push byte 39
    jmp irq_save_state

irq8:
    cli
    push byte 0
    push byte 40
    jmp irq_save_state

irq9:
    cli
    push byte 0
    push byte 41
    jmp irq_save_state

irq10:
    cli
    push byte 0
    push byte 42
    jmp irq_save_state

irq11:
    cli
    push byte 0
    push byte 43
    jmp irq_save_state

irq12:
    cli
    push byte 0
    push byte 44
    jmp irq_save_state

irq13:
    cli
    push byte 0
    push byte 45
    jmp irq_save_state

irq14:
    cli
    push byte 0
    push byte 46
    jmp irq_save_state

irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_save_state



%endif