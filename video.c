#include <apollo/video.h>
#include <apollo/io.h>

char *videoPtr = (char*) VID_MEM;
int xpos = 0, ypos = 0;

int videoPosition();
void setVideoPosition(int x, int y);
void incXpos();

int videoPosition() {
    return 2 * (xpos + ypos * VID_COL);
}

void setVideoPosition(int x, int y) {
    if (x < 0) {
        x = VID_COL - 1;
        y = (y > 0) ? y - 1 : 0;
    } else if (x >= VID_COL) {
        x = 0;
        y += 1;
    }
    if (y >= VID_LINES) {
        scroll();
        y = VID_LINES - 1;
    }
    xpos = x;
    ypos = y;
    updateCursor(xpos, ypos);
}

void clearScreen(short color) {
    int i;

    for (i = 0; i < VID_COL * VID_LINES * 2; i += 2) {
        videoPtr[i] = ' ';
        videoPtr[i + 1] = color;
    }
    setVideoPosition(0, 0);
}

void enableCursor(unsigned char start, unsigned char end) {
    outb(0x3d4, 0x0a);
    outb(0x3d5, (inb(0x3d5) & 0xc0) | start);
    outb(0x3d4, 0x0b);
    outb(0x3d5, (inb(0x3d5) & 0xe0) | end);
}

void updateCursor(unsigned char x, unsigned char y) {
    unsigned short pos = y * VID_COL + x;
    outb(0x3d4, 0x0f);
    outb(0x3d5, (unsigned char) (pos & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (unsigned char) ((pos >> 8) & 0xff));
}

void printChar(char c, short color) {
    if (c == '\n') {
        setVideoPosition(0, ypos + 1);
        return;
    }
    if (c == '\b') {
        setVideoPosition(xpos - 1, ypos);
        videoPtr[videoPosition()] = 0;
        videoPtr[videoPosition() + 1] = color;
        return;
    }

    videoPtr[videoPosition()] = c;
    videoPtr[videoPosition() + 1] = color;
    setVideoPosition(xpos + 1, ypos);
}

void printStr(char *str, short color) {
    char *c;
    for (c = str; *c != '\0'; c ++) {
        printChar(*c, color);
    }
}

void scroll() {
    int i;

    for (i = 0; i < VID_COL * (VID_LINES - 1) * 2; i ++) {
        videoPtr[i] = videoPtr[i + (VID_COL * 2)];
    }

    for (i = 0; i < VID_COL * 2; i ++) {
        videoPtr[(VID_LINES - 1) * VID_COL * 2 + i] = 0;
    }
}
