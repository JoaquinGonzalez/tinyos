#ifndef TTY_HEADER
#define TTY_HEADER

struct Screen
{
    char *vm;
    unsigned char dc;
    struct {
        unsigned int row;
        unsigned int col;
    } pos, size;
};

void inittty();
void cls();
void putch(char);
void print(char*);
void ttynewline();

#endif
