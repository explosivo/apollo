#include <apollo/video.h>

char *_videoPtr = (char*) VID_MEM;
int _videoPosition = 0;

void clearScreen(short color) {
    int i;

    for (i = 0; i < VID_COL * VID_LINES * 2; i += 2) {
        _videoPtr[i] = ' ';
        _videoPtr[i + 1] = color;
    }
    _videoPosition = 0;
}

void printChar(char c, short color) {
    if (_videoPosition >= VID_MAX) {
        scroll();
        _videoPosition = VID_COL * (VID_LINES - 1) * 2;
    }

    _videoPtr[_videoPosition] = c;
    _videoPtr[_videoPosition + 1] = color;
    _videoPosition += 2;
}

void printStr(char *str, short color) {
    if (_videoPosition >= VID_MAX) {
        scroll();
        _videoPosition = VID_COL * (VID_LINES - 1) * 2;
    }
    char *c;
    for (c = str; *c != '\0'; c ++) {
        _videoPtr[_videoPosition] = *c;
        _videoPtr[_videoPosition + 1] = color;
        _videoPosition += 2;
    }
}

void scroll() {
    int i;

    for (i = 0; i < VID_COL * (VID_LINES - 1) * 2; i ++) {
        _videoPtr[i] = _videoPtr[i + (VID_COL * 2)];
    }

    for (i = 0; i < VID_COL * 2; i ++) {
        _videoPtr[(VID_LINES - 1) * VID_COL * 2 + i] = 0;
    }
}
