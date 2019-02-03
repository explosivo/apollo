#include <apollo/video.h>
#include <apollo/io.h>
#include <stdlib.h>

void main(void) {
    unsigned char keyCode;

    clearScreen(0x40);
    printStr("a p o l l o", 0xf0);

    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);

    for (;;) {
        if ((inb(0x64) & 1) > 0) {
            keyCode = inb(0x60);
            if (keyCode < 0x80) {
                printChar(key[keyCode], 0x0f);
            }
        }
    }

    return;
}
