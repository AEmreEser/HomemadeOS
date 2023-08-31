%ifndef _GDT_INC_
%define _GDT_INC_

; GDT Table (Flat, only code and data segments)
; GDT descriptor (6 bytes)
; size 2 bytes
; address 4 bytes
gdt_start:
gdt_null:
    dd 0x0 ; 4 bytes
    dd 0x0 ; 4 bytes
gdt_code: ; code segment descriptor
    dw 0xffff ; segment limit --> all memory?
    dw 0x0 ; base address 0
    db 0x0 ; base 0 [23:16]
    db 10011010b ; present = 1, privilege = 0, type = 01, code segment = 1, conforming = 0, readable = 1, accessed = 0
    db 11001111b ; 
    db 0x0 ; base 0 [31:24]  
gdt_data: ; data segement descriptor
    dw 0xffff ; segment limit --> all memory?
    dw 0x0 ; base address 0
    db 0x0 ; base 0 [23:16]
    db 0b10010010 ; present = 1, privilege = 0, type = 01, code segment = 0, conforming = 0, readable = 1, accessed = 0
    db 0b11001111 ; 
    db 0x0 ; base 0 [31:24]
gdt_end:

gdt_descriptor:
    ; anatomy : 2 lower bytes: size, 4 higher bytes: pointer to gdt beginning
    dw gdt_end - gdt_start - 0x1 ; subtracting 1 since the size of the gdt is [1, 65536], 65536 overflows the 2 bytes assigned for size and the gdt can never be 0 -> hence the number here is actually mapped to: the number + 1
    dd gdt_start

; GDT pointers/offset --> gdt is addressed by offsets
; put these in segment regs to address into segments
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


%endif