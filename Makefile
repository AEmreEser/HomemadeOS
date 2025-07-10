MAKEFLAGS += --no-builtin-rules --no-builtin-variables

bd:=build
img:=$(bd)/os.img

emu:=qemu-system-x86_64
eflags:=--no-reboot -no-shutdown -d int,cpu_reset -drive file=$(img),format=raw,if=ide,index=0,media=disk -boot order=d -machine pc;

# IMPORTANT: make sure the assignment uses '=' and nothing else!!!
objs=$(wildcard $(bd)/*.o)
bootbin:=$(bd)/bootloader.bin
kernbin:=$(bd)/kernel.bin
bins:=$(bootbin) $(kernbin) # the order here matters !!! bootloader must come first!!!

.PHONY: all clean run

all: $(img)

run: $(img)
	$(emu) $(eflags)

$(img): $(bins) | $(bd)
	cat $^ > $@
	truncate -s 1440k $@

$(bootbin): 
	@make -C src/bootloader -f boot.make 

$(kernbin):
	@make -C src -f kernel.make 

clean: $(bd)
	-rm $(wildcard $(bd)/*)

$(bd):
	mkdir -p $(bd)
