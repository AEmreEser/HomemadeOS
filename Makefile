asm=nasm
build_dir=build
src_dir=src
inc_dir=src
drv_dir=drivers

all: $(build_dir)/os.img

$(build_dir)/os.img: $(build_dir)/kernel.bin $(build_dir)/bootloader.bin
	cat $(build_dir)/bootloader.bin $(build_dir)/kernel.bin > $(build_dir)/os.img
	truncate -s 1440k $(build_dir)/os.img

$(build_dir)/kernel.bin: $(build_dir)/kernel.o $(src_dir)/kernel_head.asm
	$(asm) $(src_dir)/kernel_head.asm -f elf -o $(build_dir)/kernel_head.o -i $(inc_dir)/
	ld -m elf_i386 -s -o $(build_dir)/kernel.bin -Ttext 0x1000 $(build_dir)/kernel_head.o $(build_dir)/kernel.o  --oformat binary 

$(build_dir)/bootloader.bin: $(src_dir)/bootloader.asm
	$(asm) $< -f bin -o $@ -i $(inc_dir)/

$(build_dir)/kernel.o: $(src_dir)/kernel.c $(drv_dir)/crtc_vga_driver.h $(drv_dir)/port_utils.h # place include directories after kernel.c
	gcc -c $< -I $(drv_dir)/ -o $@ -ffreestanding -fno-stack-protector -fno-pie -m32

