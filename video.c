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

void printStr(char *str, short color) {
    char *c;
    for (c = str; *c != '\0'; c ++) {
        _videoPtr[_videoPosition] = *c;
        _videoPtr[_videoPosition + 1] = color;
        _videoPosition += 2;
    }
}
