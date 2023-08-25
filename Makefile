asm=nasm
build_dir=build
src_dir=src
inc_dir=src

$(build_dir)/os.img: $(build_dir)/kernel.bin
	cat $(build_dir)/bootloader.bin $(build_dir)/kernel.bin > $(build_dir)/os.img
	truncate -s 1440k $(build_dir)/os.img

$(build_dir)/kernel.bin: $(src_dir)/kernel.c
	gcc -c $(src_dir)/kernel.c -o $(src_dir)/kernel.o -ffreestanding  -fno-stack-protector -fno-pie -m32
	ld -m elf_i386 -s -o $(build_dir)/kernel.bin -Ttext 0x1000 $(src_dir)/kernel.o --oformat binary 
	$(asm) $(src_dir)/bootloader.asm -f bin -o $(build_dir)/bootloader.bin -i $(inc_dir)/
