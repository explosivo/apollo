#ifndef IDT_H
#define IDT_H

struct idtDescriptor {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idtPtr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idtDescriptor idt[256];
struct idtPtr idtp;

extern void init_idt();
void initIdt();

#endif
