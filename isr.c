#include <apollo/isr.h>
#include <apollo/video.h>
#include <apollo/io.h>
#include <apollo/page.h>
#include <stdlib.h>

void interruptHandler(struct registers regs) {
    printStr("interrupt: ", 0x0f);
    printStr(itoa(regs.int_no), 0x0f);
    printChar('\n', 0x0f);

    if (regs.int_no == 14) {
        pageFault(regs);
    }
}

void interruptRequest(struct registers regs) {
    if (regs.int_no >= 40) {
        outb(0xa0, 0x20);
    }

    outb(0x20, 0x20);

    if (regs.int_no == 0x21) {
        keyboardInterrupt();
    }
}

void keyboardInterrupt() {
    unsigned char keyCode;
    if ((inb(0x64) & 1) > 0) {
        keyCode = inb(0x60);
        if (keyCode < 0x80) {
            printChar(key[keyCode], 0x0f);
        }
    }
}
