; //////////////////////////////////////////////////////////////////////////////
; // File:     Name:        port.asm                                          //
; //           Language:    x86_64 NASM assembly                              //
; //                                                                          //
; // Details:  this file holds all io port functions                          //
; //                                                                          //
; // Author:   Name:    Marijn Verschuren, Ralph Vreman                       //
; //           Email:   marijnverschuren3@gmail.com                           //
; //                                                                          //
; // Date:     2023-10-23                                                     //
; //////////////////////////////////////////////////////////////////////////////
global port_in, port_out
section .text
bits 64


port_in:
	mov dx, di
	in al, dx
	ret


port_out:
	mov dx, di
	mov ax, si
	out dx, al
	ret