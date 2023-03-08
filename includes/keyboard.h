#ifndef KEYBOARD_HEADER
#define KEYBOARD_HEADER

#define PIC1_C 0x20
#define PIC1_D 0x21
#define PIC2_C 0xa0
#define PIC2_D 0xa1

#define ICW1_DEF 0x10
#define ICW1_ICW4 0x01
#define ICW4_x86 0x01

struct IDTEntry
{
    unsigned short bl;
    unsigned short sel;
    unsigned char  zero;
    unsigned char  flags;
    unsigned short bh;
};

enum KeyCode
{
    KEY_A
};

struct Rune
{
    char c;
    unsigned long code;
};

struct KeyEvent
{
    struct Rune rune;
    enum KeyCode keycode;
    unsigned char pressed;
    unsigned char relased;
};


void initkb();
void initidt();
unsigned char inportb(unsigned short _port);
void outportb(unsigned short _port, unsigned char _data);
void picremap();

#endif
