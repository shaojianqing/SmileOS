extern initPic
extern initSystem

[section .text]

global _start

[bits 32]

_start:
	mov eax, 00011000B
	mov ss, eax
	mov esp, 0x7e00

	mov eax, 00010000B
	mov ds, eax

	mov es, eax
	mov fs, eax
	mov gs, eax

	call initPic				;Initialize the interrupt setting.
	call initSystem				;Initialize the system kernel.
	
	jmp $
