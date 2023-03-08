[org 0x7c00]
[bits 16]

; Boot loader
mov bx, 0x1000 ; Memory offset to which kernel will be loaded
mov ah, 0x02   ; Bios read sector function
mov al, 30     ; No. of sectors to read(if your kernel won't fit into 30 sectors, you may need to provide the correct no. of sectors to read)
mov ch, 0x00   ; Select cylinder 0 from harddisk
mov dh, 0x00   ; Select head 0 from hard disk
mov cl, 0x02   ; Start reading from second sector(sector just after boot sector)
int 0x13       ; Bios interrupt relating to disk functions

; Switch to protected mode
cli ; Turns interrupts off
lgdt [GDT_DESC] ; Loads our GDT

mov eax, cr0
or eax, 0x1
mov cr0, eax ; Switch to protected mode

jmp CODE_SEG:INIT_PM ; Jumps to our 32 bit mode
; Forces the cpu ro flush contents in cache memory

[bits 32]

INIT_PM:
mov ax, DATA_SEG
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

mov ebp, 0x90000
mov esp, ebp ; Updates stack segment

call 0x1000
jmp $ ; Hang

GDT_BEGIN:

GDT_NULL_DESC: ; The mandatory null descriptor
    dd 0x0
    dd 0x0

GDT_CODE_SEG:
    dw 0xffff    ; Limit
    dw 0x0       ; Base
    db 0x0       ; Base
    db 10011010b ; Flags
    db 11001111b ; Flags
    db 0x0       ; Base

GDT_DATA_SEG:
    dw 0x0ffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

GDT_END:

GDT_DESC:
    dw GDT_END - GDT_BEGIN - 1
    dd GDT_BEGIN

CODE_SEG equ GDT_CODE_SEG - GDT_BEGIN
DATA_SEG equ GDT_DATA_SEG - GDT_BEGIN

times 510-($-$$) db 0
dw 0xaa55
