%ifndef _PRINT_STR_INC_
%define _PRINT_STR_INC_

[bits 16]

print_chr_scroll_bios: ; bx must contain address of char, al must contain char ascii code 
    mov ah, 0x0e
    int 0x10
    add bx, 1
    ret

print_str_bios: ; bx must contain address of string, the string should be zero terminated
    pusha
    print_str_bios_loop:
    mov al, [bx]
    cmp al, 0
    je return_print_str_bios
    call print_chr_scroll_bios
    jmp print_str_bios_loop
    return_print_str_bios:
    popa
    ret
; #### PRINT STR END ####

[bits 32]

; CONSTANTS
VID_MEM equ 0xb8000
BLACK_ON_RED equ 0x40
VIDEO_MEMORY equ 0xB8000
WHITE_ON_BLACK equ 0x0F

; prints a null-terminated string pointed to by EBX
print_str_vid_mem:
    pusha
    mov   edx, VIDEO_MEMORY
    mov   ah, WHITE_ON_BLACK
print_string_pm_loop:
    mov   al, [ebx]
    cmp   al, 0
    je    print_string_pm_done
    mov   [edx], ax
    add   ebx, 1
    add   edx, 2
    jmp print_string_pm_loop
print_string_pm_done:
    popa
    ret

%endif