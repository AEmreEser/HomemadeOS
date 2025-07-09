asm=nasm
build_dir=build
src_dir=src
inc_dir=src
img?=os.img
kern_dir=$(src_dir)/kernel
boot_dir=$(src_dir)/bootloader
int_dir=$(kern_dir)/interrupt
drv_dir=sys_utils
tools=i686-elf-
emulator=qemu-system-x86_64
emu_opt?=-drive file=$(build_dir)/$(img),format=raw,index=0,media=disk;

.PHONY: all run rerun rebuild remove

all: $(build_dir)/$(img)

$(build_dir)/$(img): $(build_dir)/kernel.bin $(build_dir)/bootloader.o
	cat $^ > $@
	truncate -s 1440k $@

$(build_dir)/kernel.bin: $(build_dir)/kernel_head.o $(build_dir)/kernel.o $(build_dir)/interrupts.o $(kern_dir)/kernel_head.asm
	$(tools)ld -s -o $@ -Ttext 0x1000 $^ --oformat binary -nostdlib

$(build_dir)/kernel_head.o: $(kern_dir)/kernel_head.asm
	$(asm) $< -f elf -o $@ -i $(kern_dir)/

$(build_dir)/interrupts.o: $(int_dir)/isr_routines.asm
	$(asm) $< -f elf -o $@ -i $(int_dir)/

$(build_dir)/bootloader.o: $(boot_dir)/bootloader.asm
	$(asm) $< -f bin -o $@ -i $(boot_dir)/

$(build_dir)/kernel.o: $(kern_dir)/kernel.c $(drv_dir)/vga_utils.h $(drv_dir)/port_utils.h # place include directories after kernel.c
	$(tools)-gcc -c $< -I $(drv_dir)/ -o $@ -ffreestanding -fno-stack-protector -fno-pie -Wall

run: all
	$(emulator) $(emu_opt)

rerun: rebuild
	$(emulator) $(emu_opt)

rebuild: remove $(build_dir)/$(img)

remove:
	rm $(build_dir)/* -f
	mkdir -p $(build_dir)