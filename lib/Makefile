CC = gcc
CFLAGS = -Wall -O -I../include -m32 -nostdlib -nostdinc -fno-builtin
OBJS = stdio.o stdlib.o string.o

.c.o:
		@echo CC $<
		@$(CC) $(CFLAGS) -c -o $*.o $<

lib.a: $(OBJS)
		@echo AR $<
		@ar rcs lib.a $(OBJS)
		@sync

clean:
		rm -f *.o *.a
