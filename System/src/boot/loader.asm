%include "src/boot/structure.inc"	

KERNAL_ADDR            equ               0x00080000

GDT_BASE               equ               0x00007e00

IDT_BASE               equ               0x00017e00

SYS_SELECTOR           equ               0x00000008

           [bits 16]
         
           jmp enter_protect_mode
gdt:              
empty:     Descriptor 0x00000000, 0x00000000,  0x00000                  ;00000_000B
text:      Descriptor 0x00000000, 0x000fffff,  DA_C | DA_32_4K       	;00001_000B
data:      Descriptor 0x00000000, 0x000fffff,  DA_DRW | DA_32_4K   		;00010_000B
stack:     Descriptor 0x00007e00, 0x00007e00,  DA_DRWA | DA_32      	;00011_000B  

gdt_size:  dw 0xFF
gdt_base:  dd GDT_BASE

enter_protect_mode:         
	;---------------GDT TABLE-----------------;
	mov ax, 0x7e0
	mov es, ax
	mov di, 0x00           

	mov ax, 0x1860
	mov ds, ax
	mov si, gdt             
	mov cx, 0x20
	rep movsb
	;------------------------;	
	mov ax, 0x1860
	mov ds, ax
	mov byte [packageSize], 0x10
	mov byte [reserveByte], 0x00
	mov word [blockCount], 0x80
	mov word [bufferOffs], 0x00
	mov word [bufferSegm], 0x8000
	mov dword [blockNum], 0x48

	mov ah, 0x42
	mov dl, 0x80
	mov si, packageSize
	int 0x13

	mov word [blockCount], 0x40
	mov word [bufferOffs], 0x00
	mov word [bufferSegm], 0x9000
	mov dword [blockNum], 0xC8

	mov ah, 0x42
	mov dl, 0x80
	mov si, packageSize
	int 0x13

	;------------------------;
	mov bx, 0x4118
	mov ax, 0x4f02
	int 0x10 

	mov ax, 0x2180
	mov es, ax
	xor di, di

	mov cx, 0x118
	mov ax, 0x4f01
	int 0x10

	;------------------------;
	mov ax, 0x2140
	mov ds, ax
	xor bx, bx
	mov ah, 0x88
	int 0x15
	mov [ds:bx], ax	           

	;------------------------;
	mov ax, 0x6000
	mov ds, ax

	mov edx, 0x61003
	mov si, 0x0000
	mov cx, 0x10

pdbt:
	mov [ds:si], edx
	add edx, 0x1000
	add si, 0x04
	loop pdbt

	mov edx, 0x71003
	mov si, 0x0e00
	mov [ds:si], edx

	;=========================;	

	mov cx, 0x10
	mov ax, 0x6100
	mov edx, 0x0003

outer:
	mov ds, ax
	mov si, 0x0000

inner:		
	mov [ds:si], edx
	add edx, 0x1000
	add si, 0x04
	cmp si, 0x1000
	jl inner

	add ax, 0x100
	loop outer

	mov ax, 0x7100
	mov ds, ax
	mov si, 0x00
	mov edx, 0xe0000003
	mov cx, 0x400

vram:
	mov [ds:si], edx
	add edx, 0x1000
	add si, 0x04
	loop vram

	mov eax, 0x60000
	mov cr3, eax
	;------------------------;	
 
	cli

	mov ax, 0x1860 
	mov ds, ax

	mov word [ds: gdt_size], 0xFFFF                                            
	lgdt [ds: gdt_size]

	in al, 0x92                         
	or al, 0000_0010B
	out 0x92, al                                                
		                           
	mov eax, cr0
	or eax, 0x80000001
	mov cr0, eax

	jmp dword SYS_SELECTOR : KERNAL_ADDR 

packageSize: db 		0
reserveByte: db 		0
blockCount:  dw 		0
bufferOffs:  dw 		0
bufferSegm:  dw 		0
blockNum:    dq 		0
