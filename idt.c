#include <apollo/idt.h>
#include <apollo/io.h>
#include <string.h>

void setIdt(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = base & 0xffff;
    idt[num].base_hi = (base >> 16) & 0xffff;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void initIdt() {
    idtp.limit = (sizeof(struct idtDescriptor) * 256) - 1;
    idtp.base = (unsigned int) &idt;

    memset(&idt, 0, sizeof(struct idtDescriptor) * 256);

    outb(0x20, 0x11);
    outb(0xa0, 0x11);
    outb(0x21, 0x20);
    outb(0xa1, 0x28);
    outb(0x21, 0x04);
    outb(0xa1, 0x02);
    outb(0x21, 0x01);
    outb(0xa1, 0x01);
    outb(0x21, 0x0);
    outb(0xa1, 0x0);

    setIdt(0, (unsigned int) isr0, 0x08, 0x8e);
    setIdt(1, (unsigned int) isr1, 0x08, 0x8e);
    setIdt(2, (unsigned int) isr2, 0x08, 0x8e);
    setIdt(3, (unsigned int) isr3, 0x08, 0x8e);
    setIdt(4, (unsigned int) isr4, 0x08, 0x8e);
    setIdt(5, (unsigned int) isr5, 0x08, 0x8e);
    setIdt(6, (unsigned int) isr6, 0x08, 0x8e);
    setIdt(7, (unsigned int) isr7, 0x08, 0x8e);
    setIdt(8, (unsigned int) isr8, 0x08, 0x8e);
    setIdt(9, (unsigned int) isr9, 0x08, 0x8e);
    setIdt(10, (unsigned int) isr10, 0x08, 0x8e);
    setIdt(11, (unsigned int) isr11, 0x08, 0x8e);
    setIdt(12, (unsigned int) isr12, 0x08, 0x8e);
    setIdt(13, (unsigned int) isr13, 0x08, 0x8e);
    setIdt(14, (unsigned int) isr14, 0x08, 0x8e);
    setIdt(15, (unsigned int) isr15, 0x08, 0x8e);
    setIdt(16, (unsigned int) isr16, 0x08, 0x8e);
    setIdt(17, (unsigned int) isr17, 0x08, 0x8e);
    setIdt(18, (unsigned int) isr18, 0x08, 0x8e);
    setIdt(19, (unsigned int) isr19, 0x08, 0x8e);
    setIdt(20, (unsigned int) isr20, 0x08, 0x8e);
    setIdt(21, (unsigned int) isr21, 0x08, 0x8e);
    setIdt(22, (unsigned int) isr22, 0x08, 0x8e);
    setIdt(23, (unsigned int) isr23, 0x08, 0x8e);
    setIdt(24, (unsigned int) isr24, 0x08, 0x8e);
    setIdt(25, (unsigned int) isr25, 0x08, 0x8e);
    setIdt(26, (unsigned int) isr26, 0x08, 0x8e);
    setIdt(27, (unsigned int) isr27, 0x08, 0x8e);
    setIdt(28, (unsigned int) isr28, 0x08, 0x8e);
    setIdt(29, (unsigned int) isr29, 0x08, 0x8e);
    setIdt(30, (unsigned int) isr30, 0x08, 0x8e);
    setIdt(31, (unsigned int) isr31, 0x08, 0x8e);

    setIdt(32, (unsigned int) irq0, 0x08, 0x8e);
    setIdt(33, (unsigned int) irq1, 0x08, 0x8e);
    setIdt(34, (unsigned int) irq2, 0x08, 0x8e);
    setIdt(35, (unsigned int) irq3, 0x08, 0x8e);
    setIdt(36, (unsigned int) irq4, 0x08, 0x8e);
    setIdt(37, (unsigned int) irq5, 0x08, 0x8e);
    setIdt(38, (unsigned int) irq6, 0x08, 0x8e);
    setIdt(39, (unsigned int) irq7, 0x08, 0x8e);
    setIdt(40, (unsigned int) irq8, 0x08, 0x8e);
    setIdt(41, (unsigned int) irq9, 0x08, 0x8e);
    setIdt(42, (unsigned int) irq10, 0x08, 0x8e);
    setIdt(43, (unsigned int) irq11, 0x08, 0x8e);
    setIdt(44, (unsigned int) irq12, 0x08, 0x8e);
    setIdt(45, (unsigned int) irq13, 0x08, 0x8e);
    setIdt(46, (unsigned int) irq14, 0x08, 0x8e);
    setIdt(47, (unsigned int) irq15, 0x08, 0x8e);

    init_idt((unsigned int) &idtp);
}
