%include "src/kernal/const/const.inc"

global initPic
global asmIntHandler20
global asmIntHandler21
global asmIntHandler2c
global asmIntHandler2e

extern intHandler20
extern intHandler21
extern intHandler2c
extern intHandler2e

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

    mov al, 11111000B
    out 0x21, al

    mov al, 10101111B
    out 0xa1, al

	sti

    ret

asmIntHandler20:
	push ds
	pushad

	mov eax, 00010_000B
	mov ds, eax

	call intHandler20
	
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

	call intHandler2c
		
	popad 
	pop ds		
	iretd

asmIntHandler2e:
	push ds
	pushad
	
	mov eax, 00010_000B	
	mov ds, eax

	call intHandler2e
		
	popad 
	pop ds		
	iretd
