SRC = kernel.c tty.c io.c keyboard.c
OBJ = $(SRC:.c=.o)
ASMSRC = entry.asm idt.asm
ASMOBJ = $(ASMSRC:.asm=.o)
STDCFLAGS = -c -nostdinc -nostdlib -m32 -Wall -Iincludes
STDLFLAGS = -T /dev/null -m elf_i386 -Ttext 0x1000
CC = tcc
ASM = nasm
LD = ld

all: boot.bin os.img

boot.bin: boot.asm
	$(ASM) boot.asm -f bin -o boot.bin

.c.o:
	$(CC) $(STDCFLAGS) $<

entry.o: entry.asm
	$(ASM) $< -f elf32

idt.o: idt.asm
	$(ASM) $< -f elf32

os.img: $(OBJ) $(ASMOBJ)
	$(LD) $(STDLFLAGS) -o kernel.img $(ASMOBJ) $(OBJ)
	objcopy -O binary -j .text kernel.img kernel.bin
	cat boot.bin kernel.bin > $@

run:
	qemu-system-i386 -drive format=raw,file=os.img

clean:
	rm boot.bin *.o kernel.bin kernel.img os.img
