[org 0x7C00]
bits 16

.TEXT
main: ; BOOTSECTOR

    mov bp, 0x8000 ; stack base
    mov sp, bp ; stack empty

    mov ah, 0x0e ; scrollign teletype - print chr and mov cursor interrupt spec for interrupt number 10

    mov bx, os_str ; prints os name and version
    call print_str
    mov bx, version_str
    call print_str
    mov bx, endline
    call print_str

    mov [BOOT_DRIVE], dl 
    ; al : # of disk sectors to be read
    ; ch : cylinder # 0 for default hdd boot
    ; cl : sector # 1 for default hdd boot: can at the lowest be 1
    ; dh : head # 0 for default hdd boot
    ; dl : disk drive # 0x80 or 0x81 ---> will be set by the BIOS before moving exec to boot sector (x86 does this, it is not a standard etc.)
    ; stores read data at location: 0x90000
    ; bx : where to write read data, segment used: es
    mov al, 0x05
    mov ch, 0x00 ; cylinder 0
    mov cl, 0x02 ; read from after the boot sector - each sector is 512 bytes
    mov dh, 0x00 ; head 0
    mov dl, [BOOT_DRIVE]
    mov bx, 0x0000
    mov es, bx
    mov bx, 0x9000
    call read_disk_sectors
    mov cx, 0
    mov bx, 0x9000

word_monitoring_loop:
    mov dx, [bx]  
    call print_hex
    inc cx
    add bx, 2 ; address of next word - 2 bytes
    cmp cx, 0x101 ; 257 words -> enough to move into the third sector
    jne word_monitoring_loop

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
; #### PRINT STR END ####

print_hex: ; dx must contain hex number (16 bits)
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
; #### PRINT HEX END ####

read_disk_sectors:
    ; al : # of disk sectors to be read
    ; ch : cylinder # 0 for default hdd boot
    ; cl : sector # 1 for default hdd boot
    ; dh : head # 0 for default hdd boot
    ; dl : disk drive # 0x80 or 0x81 ---> will be set by the BIOS before moving exec to boot sector (x86 does this, it is not a standard etc.)
    ; stores read data at location: 0x90000
    pusha
    mov ah, 0x02
    int 0x13
check_read_fail:
    jc disk_read_fail
    popa
    ret
disk_read_fail:
    mov bx, fail_disk_str
    call print_str
    mov dl, ah
    mov dh, 0x00
    call print_hex
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
endline:
    dw 0x0a0d,0
fail_disk_str:
    db "Disk Fail Code: ", 0


BOOT_DRIVE:
    db 0
; SPECIFY THE # OF BYTES HERE!!!!

times 510-($-$$) db 0
dw 0AA55h
; END OF BOOT SECTOR - anything after this line won't initally be loaded but will be on the disk
times 256 dw 0xda12 ; 512 bytes of da12
times 256 dw 0xefce ; 512 bytes of 0xefce