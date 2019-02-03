#ifndef IO_H
#define IO_H

extern unsigned char key[];

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char value);

#endif