#include <apollo/io.h>

unsigned char key[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't',
    'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',	'm', ',', '.', '/',
    0, '*', 0, ' ', 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

unsigned char inb(unsigned short port) {
    unsigned char value;

    asm volatile ("inb %1, %0"
                : "=a"(value)
                : "Nd"(port));

    return value;
}

void outb(unsigned short port, unsigned char value) {
    asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}