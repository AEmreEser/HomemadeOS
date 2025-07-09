%ifndef _ISR_ASM_
%define _ISR_ASM_

%include "src/bootloader/GDT.inc"

[bits 32]
[extern int_handler] ; ignore the errors squiggles, this works for some reason

; following routines taken from (and slightly modified by me): http://www.osdever.net/bkerndev/index.php
isr_save_state: ; stack should already contain the error code
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
handler_call:
    call int_handler
isr_restore_state:
    pop gs
    pop fs
    pop es
    pop ds
    popa
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
    push byte 0
    push byte 1
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
    push byte 8
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
    push byte 0
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

%endif