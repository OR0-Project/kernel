; //////////////////////////////////////////////////////////////////////////////
; // File:     Name:        multiboot.asm                                     //
; //           Language:    x86_64 NASM assembly                              //
; //                                                                          //
; // Details:  this file holds the multiboot header for grub                  //
; //                                                                          //
; // Author:   Name:    Marijn Verschuren, Ralph Vreman                       //
; //           Email:   marijnverschuren3@gmail.com                           //
; //                                                                          //
; // Date:     2023-10-23                                                     //
; //////////////////////////////////////////////////////////////////////////////
section .multiboot

multiboot_header_start:
    dd 0xe85250d6										; magic number
    dd 0												; i386 protected mode code
    dd multiboot_header_end - multiboot_header_start	; header length
    dd 0x100000000 - (0xe85250d6 + 0 + (multiboot_header_end - multiboot_header_start))		; 0x100000000 - (magic + mode + header_size)

    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
multiboot_header_end: