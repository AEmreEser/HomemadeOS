MAKEFLAGS += --no-builtin-rules --no-builtin-variables

bd:=../build
inc:=./include
kernel?=kernel

cflags:=-I ./include -ffreestanding -nostdlib -nostartfiles -fno-stack-protector -fno-pie
src:=$(kernel).c system_utils.c isr.c vga_utils.c idt.c irq.c timer.c
obj:=$(patsubst %.o, $(bd)/%.o, $(src:.c=.o))

asms:=$(kernel)_head.asm isr_irq_routines.asm
asm_obj:=$(patsubst %.asm, $(bd)/%.o, $(asms))
kernbin:=$(bd)/$(kernel).bin

.PHONY: all clean

all: $(kernbin)

$(bd)/%.o: %.c | $(bd)
	i686-elf-gcc -c $< -o $@ $(cflags)

# cannot use the following with the bootloader asm files since their format is bin - not elf!
$(bd)/%.o: %.asm | $(bd)
	nasm $< -f elf -o $@ -i $(inc)

# $(bd)/kernel.o
$(kernbin): $(obj) $(asm_obj) | $(bd)
	echo $(obj) $(asm_obj)
	i686-elf-ld -s -o $@ -Ttext 0x1000 $^ --oformat binary -nostdlib

$(bd):
	mkdir -p $(bd)

clean:
	-rm $(wildcard $(bd)/*)
	@# rm $(obj)