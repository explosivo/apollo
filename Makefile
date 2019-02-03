AS=nasm
CC=gcc
LD=ld

CFLAGS=-Wall -Iinclude -m32 -O -fno-stack-protector

%.o: %.c
		$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.s
		$(AS) -f elf32 $< -o $@

kernel: loader.o video.o kernel.o io.o
		$(LD) -m elf_i386 -T link.ld -o $@ $^

clean:
		rm kernel *.o

test: kernel
		qemu-system-i386 -kernel kernel -curses
