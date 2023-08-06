org 0x7C00
bits 16


main:

    mov ah, 0x0e ; scrollign teletype - print chr and mov cursor interrupt spec for interrupt number 10

    mov al, 'H'
    int 0x10
    mov al, 'o'
    int 0x10
    mov al, 'm'
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, 'm'
    int 0x10
    mov al, 'a'
    int 0x10
    mov al, 'd'
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, 'O'
    int 0x10
    mov al, 'S'
    int 0x10

    hlt

halt:
    hlt
    jmp halt

times 510-($-$$) db 0

dw 0AA55h
