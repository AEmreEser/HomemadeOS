MAKEFLAGS += --no-builtin-rules --no-builtin-variables

bd:=build
img:=$(bd)/os.img

emu:=qemu-system-x86_64
eflags:=-d int,cpu_reset -drive file=$(img),format=raw,if=ide,index=0,media=disk -boot order=d -machine pc;
# --no-reboot -no-shutdown 
# IMPORTANT: make sure the assignment uses '=' and nothing else!!!
objs=$(wildcard $(bd)/*.o)
bootbin:=$(bd)/bootloader.bin
kernbin:=$(bd)/kernel.bin
bins:=$(bootbin) $(kernbin) # the order here matters !!! bootloader must come first!!!

.PHONY: all clean run

all: $(img)

debug: $(img)
	$(emu) $(eflags) --no-reboot -no-shutdown 

run: $(img)
	$(emu) $(eflags)

$(img): $(bins) | $(bd)
	cat $^ > $@
	truncate -s 1440k $@

$(bootbin): $(wildcard src/bootloader/*)
	@make -C src/bootloader -f boot.make 

$(kernbin): $(wildcard src/*)
	@make -C src -f kernel.make 

clean: | $(bd)
	-rm $(wildcard $(bd)/*)

$(bd):
	mkdir -p $(bd)
