#include <apollo/page.h>
#include <apollo/heap.h>
#include <apollo/video.h>
#include <apollo/panic.h>
#include <stdlib.h>
#include <string.h>

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

extern void _switchPageDir(unsigned int);
extern unsigned int placementAddr;

PageDirectory *kernelDir = 0;
PageDirectory *currentDir = 0;

unsigned int *frames;
unsigned int numFrames;


static void setFrame(unsigned int frameAddr) {
    unsigned int frame = frameAddr / 0x1000;
    unsigned int i = INDEX_FROM_BIT(frame);
    unsigned int offset = OFFSET_FROM_BIT(frame);
    frames[i] |= (0x1 << offset);
}

static void clearFrame(unsigned int frameAddr) {
    unsigned int frame = frameAddr / 0x1000;
    unsigned int i = INDEX_FROM_BIT(frame);
    unsigned int offset = OFFSET_FROM_BIT(frame);
    frames[i] &= ~(0x1 << offset);
}

static unsigned int testFrame(unsigned int frameAddr) {
    unsigned int frame = frameAddr / 0x1000;
    unsigned int i = INDEX_FROM_BIT(frame);
    unsigned int offset = OFFSET_FROM_BIT(frame);
    return frames[i] & (0x1 << offset);
}

static unsigned int firstFreeFrame() {
    unsigned int i, j;
    for (i = 0; i < INDEX_FROM_BIT(numFrames); i ++) {
        if (frames[i] != 0xffffffff) {
            for (j = 0; j < 32; j ++) {
                unsigned int check = 0x1 << j;
                if (!(frames[i] & check)) {
                    return i * 4 * 8 + j;
                }
            }
        }
    }
    return 0xffffffff;
}

void allocFrame(Page *page, int isKernel, int isWritable) {
    if (page->frame != 0) {
        return;
    } else {
        unsigned int i = firstFreeFrame();
        if (i == (unsigned int) -1) {
            panic("no free frames.");
        }
        setFrame(i * 0x1000);
        page->present = 1;
        page->rw = isWritable ? 1 : 0;
        page->user = isKernel ? 0 : 1;
        page->frame = i;
    }
}

void freeFrame(Page *page) {
    unsigned int frame;
    if (!(frame = page->frame)) {
        return;
    } else {
        clearFrame(frame);
        page->frame = 0x0;
    }
}

void initPaging() {
    unsigned int endPage = 0x1000000;
    numFrames = endPage / 0x1000;
    frames = (unsigned int*) kmalloc(INDEX_FROM_BIT(numFrames));
    memset(frames, 0, INDEX_FROM_BIT(numFrames));

    kernelDir = (PageDirectory*) kmalloca(sizeof(PageDirectory));
    memset(kernelDir, 0, sizeof(PageDirectory));
    currentDir = kernelDir;

    int i = 0;
    while (i < placementAddr) {
        allocFrame(getPage(i, 1, kernelDir), 0, 0);
        i += 0x1000;
    }

    switchPageDirectory(kernelDir);
}

void switchPageDirectory(PageDirectory *dir) {
    currentDir = dir;
    _switchPageDir((unsigned int) &dir->physicalTables);
}

Page* getPage(unsigned int addr, int make, PageDirectory *dir) {
    addr /= 0x1000;
    unsigned int i = addr / 1024;
    if (dir->tables[i]) {
        return &dir->tables[i]->pages[addr % 1024];
    } else if (make) {
        unsigned int tmp;
        dir->tables[i] = (PageTable*)kmallocap(sizeof(PageTable), &tmp);
        memset(dir->tables[i], 0, 0x1000);
        dir->physicalTables[i] = tmp | 0x7;
        return &dir->tables[i]->pages[addr % 1024];
    } else {
        return 0;
    }
}

void pageFault(struct registers regs) {
    unsigned int faultAddr;
    asm volatile ("mov %%cr2, %0" : "=r"(faultAddr));

    int present = !(regs.err_code & 0x1);
    int rw = regs.err_code & 0x2;
    int us = regs.err_code & 0x4;
    int reserved = regs.err_code &0x8;
    int id = regs.err_code & 0x10;

    unsigned short color = 0x40;

    printStr("PAGE FAULT: ", color);
    if (present) printStr("present ", color);
    if (rw) printStr("read-only ", color);
    if (us) printStr("user-mode ", color);
    if (reserved) printStr("reserved ", color);
    if (id) printStr("on ins fetch", color);
    printStr(". ", color);
    printStr("at ", color);
    printStr(itoa(faultAddr), color);
    printChar('\n', color);
    panic("page fault.");
}
