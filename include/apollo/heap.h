#ifndef HEAP_H
#define HEAP_H

unsigned int kmalloca(unsigned int sz);
unsigned int kmallocp(unsigned int sz, unsigned int *phys);
unsigned int kmallocap(unsigned int sz, unsigned int *phys);
unsigned int kmalloc(unsigned int sz);

#endif
