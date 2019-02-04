#include <apollo/video.h>
#include <apollo/io.h>
#include <apollo/gdt.h>
#include <apollo/idt.h>
#include <stdlib.h>

void main(void) {
    initGdt();
    initIdt();

    clearScreen(0x40);
    printStr("apollo ready", 0xf0);

    // disable cursor
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);

    asm("sti");

    for (;;) {
        asm("hlt");
    }

    return;
}
