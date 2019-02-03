#include <apollo/idt.h>
#include <string.h>

void initIdt() {
    idtp.limit = (sizeof(struct idtDescriptor) * 256) - 1;
    idtp.base = &idt;

    memset(&idt, 0, sizeof(struct idtDescriptor) * 256);

    init_idt();
}
