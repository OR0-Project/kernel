# kernel make file

CC = gcc
ASM = nasm
LINK = ld
EMU = qemu-system-x86_64

C_FLAGS = -Wall -fno-pie -m64 -ffreestanding -nostdlib -Iinc -c -lgcc
ASM_FLAGS = -f elf64
LINK_FLAGS = -m elf_x86_64 -n
EMU_FLAGS = -monitor tcp:localhost:5555,server,nowait

# targets
default: all

prep:
	python3 ./prep.py

clean:
	rm -rf ./build
	rm -rf ./obj
	rm -f ./inc/build.h

all: build/kernel

build/kernel: prep multiboot.o kernel.o main.o 
	$(LINK) $(LINK_FLAGS) -o build/kernel64.bin obj/multiboot.o obj/kernel.o obj/kern/kutil.o obj/kern/kmem.o obj/util/string.o obj/dev/console.o obj/io/port.o obj/arch/x86/cpu.o obj/main.o -T src/kernel.ld

# objects
main.o: obj/dev/console.o obj/io/port.o obj/kern/kutil.o obj/kern/kmem.o obj/util/string.o obj/arch/x86/cpu.o
	$(CC) src/main.c -o obj/main.o $(C_FLAGS)

obj/kern/kutil.o:
	$(CC) src/kern/kutil.c -o obj/kern/kutil.o $(C_FLAGS)

obj/kern/kmem.o:
	$(CC) src/kern/kmem.c -o obj/kern/kmem.o $(C_FLAGS)

obj/dev/console.o:
	$(CC) src/dev/console.c -o obj/dev/console.o $(C_FLAGS)

obj/io/port.o:
	$(ASM) src/io/port.asm -o obj/io/port.o $(ASM_FLAGS)

obj/util/string.o:
	$(CC) src/util/string.c -o obj/util/string.o $(C_FLAGS)

# x86 specific objects
obj/arch/x86/cpu.o:
	$(ASM) src/arch/x86/cpu.asm -o obj/arch/x86/cpu_asm.o $(ASM_FLAGS)
	$(CC) -c src/arch/x86/cpu.c -o obj/arch/x86/cpu_c.o $(C_FLAGS)
	$(LINK) $(LINK_FLAGS) --relocatable -o obj/arch/x86/cpu.o \
    		obj/arch/x86/cpu_asm.o obj/arch/x86/cpu_c.o

# Assembler stuff
kernel.o:
	$(ASM) src/kernel.asm -o obj/kernel.o $(ASM_FLAGS)

multiboot.o:
	$(ASM) src/multiboot.asm -o obj/multiboot.o $(ASM_FLAGS)
