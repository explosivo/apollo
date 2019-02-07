AS=nasm
CC=gcc
LD=ld

CFLAGS=-Wall -Iinclude -m32 -O -fno-stack-protector -Wno-main -nostdlib -nostdinc -fno-builtin -g -std=gnu89

%.o: %.c
		@echo CC $<
		@$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.s
		@echo AS $<
		@$(AS) -f elf32 $< -o $@

kernel: loader.o video.o kernel.o io.o gdt.o idt.o interrupt.o isr.o lib/lib.a heap.o mem.o page.o panic.o
		@echo LD $@
		@$(LD) -m elf_i386 -T link.ld -o $@ $^

lib/lib.a:
		@(cd lib; make)

clean:
		(cd lib; make clean)
		rm -f kernel *.o
		rm -rf iso apollo.iso

test: kernel
		qemu-system-i386 -kernel kernel -curses

testx: kernel
		qemu-system-i386 -kernel kernel

image: kernel
		@mkdir -p iso/boot/grub
		@cp kernel iso/boot
		@echo -e -n 'set timeout=15\n'\
		'set default=0\n'\
		'menuentry \"apollo\" {\n'\
		'    multiboot /boot/kernel\n'\
		'    boot\n'\
		'}' > iso/boot/grub/grub.cfg
		@grub-mkrescue iso -o apollo.iso
