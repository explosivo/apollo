#include <apollo/panic.h>
#include <apollo/video.h>

void panic(char *str) {
    printStr("KERNEL PANIC!\n", 0x40);
    printStr(str, 0x40);

    for (;;) {
        asm("hlt");
    }
}
