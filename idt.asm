extern _idt
extern _isr1handler
global _isr1
global _loadidt

idtdesc:
    dw 2048
    dd _idt

_isr1:
    pushad
    call _isr1handler
    popad
    iretd

_loadidt:
    lidt[idtdesc]
    sti
    ret
