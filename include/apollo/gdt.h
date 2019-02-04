#ifndef GDT_H
#define GDT_H

struct gdtDescriptor {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct gdtPtr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdtDescriptor gdt[5];
struct gdtPtr gp;

extern void init_gdt(unsigned int);
void initGdt();

#endif
