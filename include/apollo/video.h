#ifndef VIDEO_H
#define VIDEO_H

#define VID_COL 80
#define VID_LINES 25
#define VID_MAX ((VID_COL) * (VID_LINES) * 2)
#define VID_MEM 0xb8000

void clearScreen(short color);
void printChar(char c, short color);
void printStr(char *str, short color);
void scroll();

#endif
