#include <apollo/video.h>

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
}

void clearScreen(short color) {
    int i;

    for (i = 0; i < VID_COL * VID_LINES * 2; i += 2) {
        videoPtr[i] = ' ';
        videoPtr[i + 1] = color;
    }
    setVideoPosition(0, 0);
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
    if (videoPosition() >= VID_MAX) {
        scroll();
        setVideoPosition(0, VID_LINES - 1);
    }
    char *c;
    for (c = str; *c != '\0'; c ++) {
        videoPtr[videoPosition()] = *c;
        videoPtr[videoPosition() + 1] = color;
        setVideoPosition(xpos + 1, ypos);
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
