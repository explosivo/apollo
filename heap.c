#include <apollo/heap.h>

extern unsigned int end;
unsigned int placementAddr = (unsigned int) &end;

unsigned int _kmalloc(unsigned int sz, int align, unsigned int *phys) {
    if (align == 1 && (placementAddr & 0xfffff000)) {
        placementAddr &= 0xfffff000;
        placementAddr += 0x1000;
    }
    if (phys) {
        *phys = placementAddr;
    }
    unsigned int tmp = placementAddr;
    placementAddr += sz;
    return tmp;
}

unsigned int kmalloca(unsigned int sz) {
    return _kmalloc(sz, 1, 0);
}

unsigned int kmallocp(unsigned int sz, unsigned int *phys) {
    return _kmalloc(sz, 0, phys);    
}

unsigned int kmallocap(unsigned int sz, unsigned int *phys) {
    return _kmalloc(sz, 1, phys);
}

unsigned int kmalloc(unsigned int sz) {
    return _kmalloc(sz, 0, 0);
}
