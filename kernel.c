#include <apollo/video.h>
#include <apollo/io.h>
#include <apollo/gdt.h>
#include <apollo/idt.h>
#include <apollo/page.h>
#include <stdlib.h>

void main(void) {
    enableCursor(14, 15);
    clearScreen(0x07);

    printStr("[initializing Global Descriptor Table]\n", 0xa0);
    initGdt();
    printStr("[initializing Interrupt Descriptor Table]\n", 0xa0);
    initIdt();
    printStr("[initializing Paging]\n", 0xa0);
    initPaging();

    asm("sti");

    printStr("good apollo, i am ready to burn star IV\n", 0x74);

    for (;;) {
        asm("hlt");
    }

    return;
}
