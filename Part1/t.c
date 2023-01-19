#include <stdio.h>

typedef unsigned int u32;

char *ctable = "0123456789ABCDEF";
int  BASE = 10;

void rpu(u32 x)
{
        char c;
        if (x) {
                c = ctable[x % BASE];
                rpu(x / BASE);
                putchar(c);
        }
}

void printu(u32 x)
{
        x == 0 ? putchar('0') : rpu(x);
        putchar(' ');
}

/* int  printx(u32 x) which print x in HEX   (prefixed with 0x ) */
/* int  printd(int x) which print an integer (x may be negative!!!) */

int main(void)
{
        puts("Hello, world!");
}
