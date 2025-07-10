[bits 32]
[extern kmain] ; referencing external symbol kmain

global _start
_start:
call kmain

jmp $