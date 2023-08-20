[org 0x7c00]
[bits 16]
main: ; BOOTSECTOR

    mov bp, 0x8000 ; stack base
    mov sp, bp ; stack empty

    mov ah, 0x0e
    mov bx, os_str ; prints os name and version
    call print_str_bios
    mov bx, version_str
    call print_str_bios
    mov bx, endline

    jmp switch_to_pm


%include "src/GDT.inc"
%include "src/print_str.inc"
%include "src/read_disk_sectors.inc"
%include "src/print_hex_bios.inc"
%include "src/switch_to_pm.inc"

BOOT_DRIVE: db 0
; SPECIFY THE # OF BYTES HERE!!!! -- or do not place anyting below!!!


[bits 32]
begin_pm:

    mov ebx, pm_str ; used this message just to test if it works
    call print_str_vid_mem ; video memory cause cannot use bios routines

    jmp halt

halt:
    hlt
    jmp halt

pm_str: db "Booted into 32 bit protected mode",0
os_str: db "HomemadeOS",0
version_str: db " 0.1",0
endline: dw 0x0a0d,0 ; endline + carriage return


times 510-($-$$) db 0
dw 0AA55h