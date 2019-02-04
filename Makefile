AS=nasm
CC=gcc
LD=ld

CFLAGS=-Wall -Iinclude -m32 -O -fno-stack-protector -Wno-main -nostdlib -nostdinc -fno-builtin -g

%.o: %.c
		@echo CC $<
		@$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.s
		@echo AS $<
		@$(AS) -f elf32 $< -o $@

kernel: loader.o video.o kernel.o io.o gdt.o idt.o interrupt.o isr.o lib/lib.a
		@echo LD $@
		@$(LD) -m elf_i386 -T link.ld -o $@ $^

lib/lib.a:
		@(cd lib; make)

clean:
		(cd lib; make clean)
		rm kernel *.o

test: kernel
		qemu-system-i386 -kernel kernel -curses

testx: kernel
		qemu-system-i386 -kernel kernel
