%include "src/kernal/const/const.inc"

global initPic
global asmIntHandler20
global asmIntHandler21
global asmIntHandler2c

extern intHandler21
extern intHandler2c

[bits 32]

initPic:
    mov al, 0x11
    out 0x20, al
    out 0xa0, al

    mov al, 0x20
    out 0x21, al

    mov al, 0x28
    out 0xa1, al

    mov al, 0x04
    out 0x21, al

    mov al, 0x02
    out 0xa1, al

    mov al, 0x01
    out 0x21, al
    out 0xa1, al

    mov al, 11111001B
    out 0x21, al

    mov al, 11101111B
    out 0xa1, al

	sti

    ret

asmIntHandler20:
	push ds
	pushad

	mov eax, 00010_000B
	mov ds, eax
	
	popad
	pop ds
	iretd

asmIntHandler21:
	push ds
	pushad

	mov eax, 00010_000B
	mov ds, eax

	call intHandler21
	
	popad
	pop ds
	iretd

asmIntHandler2c:
	push ds
	pushad
	
	mov eax, 00010_000B	
	mov ds, eax

	mov al, 0x64
	out 0xa0, al
	mov al, 0x62
	out 0x20, al
	in  al, 0x60

	call intHandler2c
		
	popad 
	pop ds		
	iretd
