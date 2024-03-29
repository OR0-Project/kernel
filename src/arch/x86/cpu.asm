; //////////////////////////////////////////////////////////////////////////////
; // File:     Name:        cpu.asm                                           //
; //           Language:    x86_64 NASM assembly                              //
; //                                                                          //
; // Details:  this file holds all x86 cpu functions                          //
; //                                                                          //
; // Author:   Name:    Marijn Verschuren, Ralph Vreman                       //
; //           Email:   marijnverschuren3@gmail.com                           //
; //                                                                          //
; // Date:     2023-10-23                                                     //
; //////////////////////////////////////////////////////////////////////////////
global cpuid, write_msr, read_msr, read_tsc
section .text
bits 64


cpuid:
	; the result pointer for edx is already in r8
	mov r9, rcx                     ; move ecx result pointer into r9
	mov r10, rdx                    ; move ebx result pointer into r10
	mov r11, rsi                    ; move eax result pointer into r11
	mov rax, rdi                    ; load the leaf into eax
	cpuid                           ; call cpuid
	mov [r11], eax                  ; move the result for eax from cpuid into memory
	mov [r10], ebx                  ; move the result for ebx from cpuid into memory
	mov [r9], ecx                   ; move the result for ecx from cpuid into memory
	mov [r8], edx                   ; move the result for edx from cpuid into memory
	ret


write_msr:
	mov ecx, edi
	mov rax, rsi
	wrmsr
	ret


read_msr:
	mov ecx, edi
	rdmsr
	ret


read_tsc:
	xor rax, rax
	rdtsc
	shl rdx, 32
	or rax, rdx
	ret
