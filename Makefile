asm=nasm
build_dir=build
src_dir=src
kern_dir=src/kernel
int_dir=src/kernel/interrupt
boot_dir=src/bootloader
inc_dir=src
drv_dir=drivers

all: $(build_dir)/os.img

$(build_dir)/os.img: $(build_dir)/kernel.bin $(build_dir)/bootloader.o
	cat $(build_dir)/bootloader.o $(build_dir)/kernel.bin > $(build_dir)/os.img
	truncate -s 1440k $(build_dir)/os.img

$(build_dir)/kernel.bin: $(build_dir)/kernel.o $(build_dir)/interrupts.o $(kern_dir)/kernel_head.asm
	$(asm) $(kern_dir)/kernel_head.asm -f elf -o $(build_dir)/kernel_head.o -i $(kern_dir)/
	i686-elf-ld -s -o $(build_dir)/kernel.bin -Ttext 0x1000 $(build_dir)/interrupts.o $(build_dir)/kernel_head.o $(build_dir)/kernel.o  --oformat binary -nostdlib

$(build_dir)/interrupts.o: $(int_dir)/isr_routines.asm
	$(asm) $< -f elf -o $(build_dir)/interrupts.o -i $(int_dir)/

$(build_dir)/bootloader.o: $(boot_dir)/bootloader.asm
	$(asm) $< -f bin -o $(build_dir)/bootloader.o -i $(boot_dir)/

$(build_dir)/kernel.o: $(kern_dir)/kernel.c $(drv_dir)/crtc_vga_driver.h $(drv_dir)/port_utils.h # place include directories after kernel.c
	i686-elf-gcc -c $< -I $(drv_dir)/ -o $@ -ffreestanding -fno-stack-protector -fno-pie -Wall

rerun: rebuild
	qemu-system-x86_64  -drive file=build/os.img,format=raw,index=0,media=disk;

rebuild: remove $(build_dir)/os.img

remove:
	rm $(build_dir)/* -f