#ifndef STDLIB_H
#define STDLIB_H

char *itoa(int num) {
    static char str[12] = "";
    char c;
    int i = 0, len, neg = 0;

    if (num < 0) {
        neg = 1;
        num = -num;
    }

    while (num != 0) {
        str[i] = '0' + (num % 10);

        num /= 10;
        i ++;
    }

    if (neg) {
        str[i] = '-';
        i ++;
    }

    str[i] = '\0';
    len = i;
    for (i = 0; i < len / 2; i ++) {
        c = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 -i] = c;
    }

    return str;
}

#endif