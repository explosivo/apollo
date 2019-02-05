#ifndef PAGING_H
#define PAGING_H

#include <apollo/isr.h>

typedef struct page {
    unsigned int present: 1;
    unsigned int rw: 1;
    unsigned int user: 1;
    unsigned int accessed: 1;
    unsigned int dirty: 1;
    unsigned int unused: 7;
    unsigned int frame: 20;
} Page;

typedef struct pageTable {
    Page pages[1024];
} PageTable;

typedef struct pageDirectory {
    PageTable *tables[1024];
    unsigned int physicalTables[1024];
    unsigned int physicalAddr;
} PageDirectory;

void initPaging();
void switchPageDirectory(PageDirectory *dir);
Page* getPage(unsigned int addr, int make, PageDirectory *dir);
void pageFault(struct registers regs);

#endif
