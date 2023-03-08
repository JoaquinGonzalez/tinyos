#include <tty.h>

struct Screen scr;

void
inittty()
{
    scr.vm = (char*)0xb8000;
    scr.dc = 0x0f;
    scr.size.row = 25*2;
    scr.size.col = 80*2;
    scr.pos.row = 0;
    scr.pos.col = 0;
}

void
cls()
{
    unsigned int i;

    for (i = 0; i < scr.size.col * scr.size.row; i++)
        *(scr.vm+i) = 0;
    scr.pos.row = 0;
    scr.pos.col = 0;
}

void
putc(char c)
{
    unsigned int i;

    i = scr.pos.row * scr.size.col + scr.pos.col;
    *(scr.vm+i) = c;
    *(scr.vm+i+1) = scr.dc;
    scr.pos.col += 2;
}

void
print(char *str)
{
    unsigned int i = 0;
    char c;

    while (*(str+i) != '\0') {
        c = *(str+i);

        if (c == '\n') {
            scr.pos.row++;
            scr.pos.col = 0;
        } else {
            putc(c);
        }
        i++;
    }
}

void
ttynewline()
{
    scr.pos.row++;
    scr.pos.col = 0;
}
