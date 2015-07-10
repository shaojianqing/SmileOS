%include "src/kernal/const/const.inc"	

global inByte
global loadTr
global outByte
global loadGdtr
global loadIdtr
global readPort
global readHardDisk
global switchProcess
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

loadTr:
	ltr [esp+4]
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

switchProcess:
	jmp far [esp+4]
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


