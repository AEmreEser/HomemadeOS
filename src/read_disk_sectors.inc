%ifndef _READ_DISK_SECTORS_INC_
%define _READ_DISK_SECTORS_INC_

fail_disk_str: db "Disk Fail Code: ", 0

read_disk_sectors:
    ; al : # of disk sectors to be read
    ; ch : cylinder # 0 for default hdd boot
    ; cl : sector # 1 for default hdd boot
    ; dh : head # 0 for default hdd boot
    ; dl : disk drive # 0x80 or 0x81 ---> will be set by the BIOS before moving exec to boot sector (x86 does this, it is not a standard etc.)
    ; stores read data at location: 0x9000
    pusha
    mov ah, 0x02
    int 0x13
check_read_fail:
    jc disk_read_fail
    popa
    ret
disk_read_fail:
    mov bx, fail_disk_str
    call print_str_bios
    mov dl, ah
    mov dh, 0x00
    call print_hex_bios
    popa
    ret

%endif