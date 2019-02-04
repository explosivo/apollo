#include <string.h>
#include <stddef.h>

void* memset(void *str, int c, size_t n) {
    int i;
    unsigned char *p = str;
    for (i = 0; i < n; i ++) {
        p[i] = (unsigned char) c;
    }
    return str;
}
