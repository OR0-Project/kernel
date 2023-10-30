; //////////////////////////////////////////////////////////////////////////////
; // File:     Name:        kernel.asm                                        //
; //           Language:    x86_64 NASM assembly                              //
; //                                                                          //
; // Details:  this file holds the entrypoint for the kernel                  //
; //                                                                          //
; // Author:   Name:    Marijn Verschuren, Ralph Vreman                       //
; //           Email:   marijnverschuren3@gmail.com                           //
; //                                                                          //
; // Date:     2023-10-23                                                     //
; //////////////////////////////////////////////////////////////////////////////
global _kernel_main
extern kernel_main



; ///////////////////////////////////////////////////////////////////////////
; entry point ///////////////////////////////////////////////////////////////
section .text
bits 32
_kernel_main:
	mov esp, stack_top

	call setup_page_tables
	call enable_paging

	lgdt [gdt64.pointer]
	jmp gdt64.code_segment:_kernel_main64
	hlt


setup_page_tables:
	mov eax, page_table_l3
	or eax, 0b11			; bit-0: present, bit-1: read/write
	mov [page_table_l4], eax

	mov eax, page_table_l2
	or eax, 0b11			; bit-0: present, bit-1: read/write
	mov [page_table_l3], eax

	mov ecx, 0

.loop:
	mov eax, 0x200000		; 2 MiB
	mul ecx
	or eax, 0b10000011		; bit-7: huge page
	mov [page_table_l2 + ecx * 8], eax

	inc ecx
	cmp ecx, 512
	jne .loop

	ret


enable_paging:
	mov eax, page_table_l4
	mov cr3, eax
	
	mov eax, cr4
	or eax, 1 << 5			; set PAE flag
	mov cr4, eax
	
	mov ecx, 0xC0000080		; magic number for the EFER register
	rdmsr					; load the EFER register to eax
	or eax, 1 << 8			; set long mode enable flag
	wrmsr					; store the eax to the EFER register
	
	mov eax, cr0
	or eax, 1 << 31			; set paging flag
	mov cr0, eax
	
	ret



; ///////////////////////////////////////////////////////////////////////////
; 64 bit entry //////////////////////////////////////////////////////////////
bits 64
_kernel_main64:
	xor ax, ax
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call kernel_main
	hlt



; ///////////////////////////////////////////////////////////////////////////
; page tables ///////////////////////////////////////////////////////////////
section .bss
align 4096

page_table_l4:
	resb 4096
page_table_l3:
	resb 4096
page_table_l2:
	resb 4096



; ///////////////////////////////////////////////////////////////////////////
; stack memory //////////////////////////////////////////////////////////////
stack_bottom:
	resb 4096 * 4 ; 16 KiB
stack_top:



; ///////////////////////////////////////////////////////////////////////////
; GDT ///////////////////////////////////////////////////////////////////////
section .rodata
gdt64:
	dq 0 ; zero entry
.code_segment: equ $ - gdt64
	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) ; code segment
.pointer:
	dw $ - gdt64 - 1
	dq gdt64

