#include <apollo/gdt.h>

void setGdt(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void initGdt() {
    gp.limit = (sizeof(struct gdtDescriptor) * 3) - 1;
    gp.base = &gdt;

    setGdt(0, 0, 0, 0, 0);
    setGdt(1, 0, 0xffffffff, 0x9a, 0xcf);
    setGdt(2, 0, 0xffffffff, 0x92, 0xcf);
    init_gdt();
}
