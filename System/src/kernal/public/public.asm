%include "src/kernal/const/const.inc"	

global inByte
global outByte
global loadGdtr
global loadIdtr
global readPort
global initTiming
global readHardDisk
global clearInterrupt
global setupInterrupt
global setupInterruptHlt

[bits 32]

loadGdtr:
	mov ax, [esp+4]
	mov [esp+6], ax
	lgdt [esp+6]
	ret

loadIdtr:
	mov ax, [esp+4]
	mov [esp+6],ax
	lidt [esp+6]
	ret

initTiming:
	mov al, 0x34
	out PIT_CTRL, al
	
	mov al, 0x9c
	out PIT_CNT0, al

	mov al, 0x2e
	out PIT_CNT0, al

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


