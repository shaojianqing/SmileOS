%include "src/kernal/const/const.inc"	

global inByte
global outByte
global initPic
global memCopy
global readPort
global writeRAM
global writeVRAM
global initMouse
global initTiming
global readHardDisk
global initKeyboard
global clearInterrupt
global setupInterrupt
global setupInterruptHlt

[bits 32]

writeVRAM:
    mov ax, 00000100_000B
    mov gs, ax
    mov ebx, [esp + 4]
    mov dl,  [esp + 8]
    mov byte [gs:ebx], dl
    mov dl,  [esp + 12]
    mov byte [gs:ebx + 1], dl
    mov dl,  [esp + 16]
    mov byte [gs:ebx + 2], dl
    ret

writeRAM:
    mov ax,  00000010_000B
    mov ds,  ax
    mov ebx, [esp + 4]
    mov dl,  [esp + 8]
    mov byte [ds:ebx], dl
    ret

memCopy:
    mov ax,  00000010_000B
    mov ds,  ax
    mov edi, [esp + 4]
    mov esi, [esp + 8]
    mov ecx, [esp + 12]
copy:   mov dl,  [ds:esi]
    mov byte [ds:edi], dl
    inc esi
    inc edi
    loop copy
    ret

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

waitKBCReady:
readKBC:in al, PORT_KEYSTA
	and al, 0x02
	jnz readKBC
	ret

initTiming:
	mov al, 0x34
	out PIT_CTRL, al
	
	mov al, 0x9c
	out PIT_CNT0, al

	mov al, 0x2e
	out PIT_CNT0, al

	ret

initKeyboard:
	call waitKBCReady
	mov al, KEYCMD_WRITE_MODE
	out PORT_KEYCMD, al
	call waitKBCReady
	mov al, KBC_MODE
	out PORT_KEYDAT, al
	ret

initMouse:
	call waitKBCReady
	mov al, KEYCMD_SENDTO_MOUSE
	out PORT_KEYCMD, al
	call waitKBCReady
	mov al, MOUSECMD_ENABLE
	out PORT_KEYDAT, al
	ret

clearInterrupt:
	cli
	ret

setupInterrupt:
	sti
	ret

setupInterruptHlt:
	sti
	hlt
	ret

outByte:
	mov edx, [esp+4]
	mov al, [esp+8]
	out dx, al
	nop
	nop
	ret

inByte:
	mov edx, [esp+4]
	xor eax, eax
	in al, dx
	nop
	nop
	ret

readPort:
	mov edx, [esp+4]
	mov edi, [esp+8]
	mov ecx, [esp+12]
	shr ecx, 1
	cld
	rep insw
	ret


