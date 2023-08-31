
[bits 16]

jmp end ; for if the include directive is in between executed code


fail_disk_str: db "Disk Fail Code: ", 0

read_disk_sectors:

    ; bx : offset where we want the data to be read to
    ; al : # of disk sectors to be read
    ; ch : cylinder # 0 for default hdd boot
    ; cl : sector # 1 for default hdd boot
    ; dh : head # 0 for default hdd boot
    ; dl : disk drive # 0x80 or 0x81 ---> will be set by the BIOS before moving exec to boot sector
    mov ah, 0x02
    int 0x13
    ret
check_read_fail:
    jc disk_read_fail
    ret
disk_read_fail:
    mov bx, fail_disk_str
    call print_str_bios
    mov dl, ah
    mov dh, 0x00
    call print_hex_bios
    ret
end: