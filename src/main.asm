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

    hlt

halt:
    hlt
    jmp halt

print_chr_scroll: ; bx must contain address of char, al must contain char ascii code
    add bx, 1
    int 0x10
    ret

print_str: ; bx must contain address of string, the string should be zero terminated
    mov al, [bx]
    cmp al, 0
    je return
    call print_chr_scroll
    jmp print_str
return:
    ret



.DATA
os_str db "HomemadeOS",0
version_str db " 0.1",0



times 510-($-$$) db 0
dw 0AA55h
