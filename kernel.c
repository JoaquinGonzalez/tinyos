#include <tty.h>
#include <keyboard.h>

int
_start()
{
    char msg[] = "Hello, World!\n";
    char msg2[] = "by Joaquin Gonzalez\n";

    inittty();
    initkb();
    cls();
    print(msg);
    print(msg2);
    return 0;
}
