#include <apollo/gdt.h>

void setGdt(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void initGdt() {
    gp.limit = (sizeof(struct gdtDescriptor) * 3) - 1;
    gp.base = (unsigned int) &gdt;

    setGdt(0, 0, 0, 0, 0);
    setGdt(1, 0, 0xffffffff, 0x9a, 0xcf);
    setGdt(2, 0, 0xffffffff, 0x92, 0xcf);
    setGdt(3, 0, 0xffffffff, 0xfa, 0xcf);
    setGdt(4, 0, 0xffffffff, 0xf2, 0xcf);

    init_gdt((unsigned int) &gp);
}
