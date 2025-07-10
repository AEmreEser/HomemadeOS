MAKEFLAGS += --no-builtin-rules --no-builtin-variables
asm:=nasm
bd:=../../build
boot:=.

$(bd)/bootloader.bin: bootloader.asm | $(bd)
	$(asm) $< -f bin -o $@ -i $(boot)

$(bd):
	mkdir -p $(bd)
