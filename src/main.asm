[org 0x7C00] ; harcoded bios boot sector load address
bits 16

out_char_scroll:   ; bx must contain the address of char, outputs byte @ bx, adds 1 tob
    mov al, [bx] 
    add bx, 1
    int 0x10


out_str:
; strings will be \0 terminated


main:

    mov ah, 0x0e ; scrollign teletype - print chr and mov cursor interrupt spec for interrupt number 10

    mov bx, osname

    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    mov al, [bx]
    add bx, 1
    int 0x10
    
    hlt

halt:
    hlt
    jmp halt

osname:
    db 'HomemadeOS'
version:
    db  ' 0.1',0    ; 0: termination character


times 510-($-$$) db 0

dw 0AA55h
