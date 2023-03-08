#include <keyboard.h>
#include <tty.h>

extern void _loadidt();
extern void _isr1handler();

struct IDTEntry _idt[256];
extern unsigned int _isr1;
unsigned int base;

void
handlekeypress(int code)
{
    char sc[58];
    sc[0] = 0;
    sc[1] = 0;
    sc[2] = '1';
    sc[3] = '2';
    sc[4] = '3';
    sc[5] = '4';
    sc[6] = '5';
    sc[7] = '6';
    sc[8] = '7';
    sc[9] = '8';
    sc[10] = '9';
    sc[11] = '0';
    sc[12] = '-';
    sc[13] = '=';
    sc[14] = 0;
    sc[15] = 0;
    sc[16] = 'Q';
    sc[17] = 'W';
    sc[18] = 'E';
    sc[19] = 'R';
    sc[20] = 'T';
    sc[21] = 'Y';
    sc[22] = 'U';
    sc[23] = 'I';
    sc[24] = 'O';
    sc[25] = 'P';
    sc[26] = '[';
    sc[27] = ']';
    sc[28] = 0;
    sc[29] = 0;
    sc[30] = 'A';
    sc[31] = 'S';
    sc[32] = 'D';
    sc[33] = 'F';
    sc[34] = 'G';
    sc[35] = 'H';
    sc[36] = 'J';
    sc[37] = 'K';
    sc[38] = 'L';
    sc[39] = ';';
    sc[40] = '\'';
    sc[41] = '`';
    sc[42] = 0;
    sc[43] = '\\';
    sc[44] = 'Z';
    sc[45] = 'X';
    sc[46] = 'C';
    sc[47] = 'V';
    sc[48] = 'B';
    sc[49] = 'N';
    sc[50] = 'M';
    sc[51] = ',';
    sc[52] = '.';
    sc[53] = '/';
    sc[54] = 0;
    sc[55] = '*';
    sc[56] = 0;
    sc[57] = ' ';

    if (code == 0x1c) {
        ttynewline();
    } else if (code < 0x3a) {
        putc(sc[code]);
    }
}

extern void
_isr1handler()
{
    handlekeypress(inportb(0x60));
    outportb(0x20, 0x20);
    outportb(0xa0, 0x20);
}

void
picremap()
{
    unsigned char a, b;

    a = inportb(PIC1_D);
    b = inportb(PIC2_D);

    outportb(PIC1_C, ICW1_DEF | ICW1_ICW4);
    outportb(PIC2_C, ICW1_DEF | ICW1_ICW4);

    outportb(PIC1_D, 0);
    outportb(PIC2_D, 8);

    outportb(PIC1_D, 4);
    outportb(PIC2_D, 2);

    outportb(PIC1_D, ICW4_x86);
    outportb(PIC2_D, ICW4_x86);

    outportb(PIC1_D, a);
    outportb(PIC2_D, b);
}

unsigned char
inportb(unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void
outportb(unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void
initidt()
{
    _idt[1].bl = (base & 0xFFFF);
    _idt[1].bh = (base >> 16) & 0xFFFF;
    _idt[1].sel = 0x08;
    _idt[1].zero = 0;
    _idt[1].flags = 0x8e;

    picremap();

    outportb(0x21, 0xfd);
    outportb(0xa1, 0xff);

    _loadidt();
}

void
initkb()
{
    base = (unsigned int)&_isr1;
    initidt();
}
