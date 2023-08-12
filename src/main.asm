[org 0x7C00]
bits 16

.TEXT
main:

    mov bp, 0x8000 ; stack base
    mov sp, bp ; stack empty

    mov ah, 0x0e ; scrollign teletype - print chr and mov cursor interrupt spec for interrupt number 10

    mov bx, os_str ; prints os name and version
    call print_str
    mov bx, version_str
    call print_str
    
    mov dx, 0x2345
    call print_hex
    mov dx, 0x2345
    call print_hex

    hlt

halt:
    hlt
    jmp halt

print_chr_scroll: ; bx must contain address of char, al must contain char ascii code 
    mov ah, 0x0e
    int 0x10
    add bx, 1
    ret

print_str: ; bx must contain address of string, the string should be zero terminated
    pusha
print_str_loop:
    mov al, [bx]
    cmp al, 0
    je return_print_str
    call print_chr_scroll
    jmp print_str_loop
return_print_str:
    popa
    ret



print_hex:
    pusha
    mov cx, 4 ; counter

hex_loop:
    mov ax, dx ; copy hex
    and ax, 0xf ; last digit in ax
    shr dx, 4 ; move to next digit

    cmp ax, 0xa
    jl cont

    add ax, 0x31 ; decimal 49 : difference between ascii a and 0

    cont:
    mov bx, hex_base
    add bx, 2
    sub cx, 1
    add bx, cx ; position cursor in hex_out
    add [bx], ax ; add ascii difference between 0 and the ascii code for hex digit

    cmp cx, 0 ; test if all 4 digits have been placed
    jne hex_loop

    mov bx, hex_base
    call print_str

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


; global variables
.DATA
hex_base: 
    db "0x0000",0


os_str: 
    db "HomemadeOS",0
version_str: 
    db " 0.1",0


times 510-($-$$) db 0
dw 0AA55h
