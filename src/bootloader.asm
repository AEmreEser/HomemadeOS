[org 0x7c00]
[bits 16]

init:
MOV EBP, 0x9000 ; initialize stack
MOV ESP, EBP
mov [BOOT_DRIVE], dl ; boot drive code moved into dl by bios, better not lose this :)

reset_disks:
mov ah,00
int 13h ; reset disk device

jmp end_of_include ; jump over bios read disk routine

%include "src/read_disk_sectors.inc"
%include "src/print_str.inc"
%include "src/print_hex_bios.inc"
%include "src/GDT.inc"

end_of_include:

;load kernel to memory
load_sectors:
pusha

mov ax, 0x0
mov es, ax      ; not using any segment offsets 
mov bx, 0x1000  ; place read data at this address 
                ; all addresses in the compiled kernel code are offsetted by 0x1000
mov al, 15      ; read 15 sectors
mov ch, 00      ; cylinder 0
mov cl, 02      ; Sector to begin reading at: 2
                ; the first sector is the one containing this piece of code
mov dh, 00      ; Head = 0
mov dl, [BOOT_DRIVE]          

call read_disk_sectors

popa


switch_pm:
cli

mov ax, 0x0
mov ds, ax 
  
lgdt [gdt_descriptor]
mov eax , cr0
or eax , 0x1

mov cr0 , eax



jmp CODE_SEG:init_pm ; far jump updates cs to CODE_SEG's value

[bits 32]

init_pm:
 
MOV AX, DATA_SEG 
MOV DS, AX
MOV SS, AX
MOV ES, AX

MOV EBP, 0x9000 ; re-initialize stack
MOV ESP, EBP 

kernel_call: ; never return
call 0x1000; jump to kernel
 
jmp $ ; jump forever

BOOT_DRIVE db 0 

times 510 -( $ - $$ ) db 0 
dw 0xaa55