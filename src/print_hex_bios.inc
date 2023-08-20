%ifndef _PRINT_HEX_BIOS_INC_
%define _PRINT_HEX_BIOS_INC_

%include "src/print_str.inc"

[bits 16]

print_hex_bios: ; dx must contain hex number (16 bits)
    pusha
    mov cx, 4 ; counter

    hex_loop:
    mov ax, dx ; copy hex
    and ax, 0xf ; last digit in ax
    shr dx, 4 ; move to next digit

    cmp ax, 0xa
    jl cont

    add ax, 0x27 ; decimal 49 : difference between ascii a and 0, since a will contain number > 10 already we must store 39

    cont:
    mov bx, hex_base
    add bx, 2
    sub cx, 1
    add bx, cx ; position cursor in hex_out
    add [bx], ax ; add ascii difference between 0 and the ascii code for hex digit

    cmp cx, 0 ; test if all 4 digits have been placed
    jne hex_loop

    mov bx, hex_base
    call print_str_bios

    restore_hex_base:
    mov bx, hex_base
    add bx, 2 ; 0x
    mov cx, 4
    restore_hex_base_loop:
    mov byte [bx], '0'
    add bx, 1
    dec cx
    cmp cx, 0
    jne restore_hex_base_loop

    popa
    ret
; #### PRINT HEX END ####


hex_base: db "0x0000",0

%endif