# kernel make file

CC = gcc
ASM = nasm
LINK = ld
EMU = qemu-system-x86_64

# C_FLAGS = -Wall -fno-pie -m64 -ffreestanding -nostdlib -Iinc -c -lgcc
# ASM_FLAGS = -f elf64
# LINK_FLAGS = -m elf_x86_64 -n
EMU_FLAGS = -monitor tcp:localhost:5555,server,nowait

# TODO reimplement for efi kernel