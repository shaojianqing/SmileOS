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
vram:      Descriptor 0xe0000000, 0x000fffff,  DA_DRW | DA_32_4K     	;00100_000B 
time:      Descriptor 0x00020400, 0x000fffff,  DA_CR | DA_32         	;00101_000B   
board:     Descriptor 0x00020400, 0x000fffff,  DA_CR | DA_32         	;00110_000B
mouse:     Descriptor 0x00020800, 0x000fffff,  DA_CR | DA_32         	;00111_000B
gate: 	   Descriptor 0x00024000, 0x0000000f,  DA_C | DA_32          	;01000_000B
call_gate: Gate 0101_000B, 0x00000000, 0x0000, DA_386CGate | DA_DPL3	;01001_000B

idt:
time_gate: Gate 0101_000B, 0x00000000, 0x0000, DA_386IGate
board_gate:Gate 0110_000B, 0x00000000, 0x0000, DA_386IGate
mouse_gate:Gate 0111_000B, 0x00000000, 0x0000, DA_386IGate      

gdt_size:  dw 0x37
gdt_base:  dd GDT_BASE 

idt_size:  dw 0x7ff
idt_base:  dd IDT_BASE

enter_protect_mode: 
         
       ;---------------GDT TABLE-----------------;
       mov ax, 0x7e0
       mov es, ax
       mov di, 0x00           

       mov ax, 0x1860
       mov ds, ax
       mov si, gdt             
       mov cx, 0x40
       rep movsb

       ;--------------IDT TABLE-----------------;
       mov ax, 0x17e0 
       mov es, ax   
       mov di, 0x20*8
       
       mov ax, 0x1860 
       mov ds, ax
       mov si, time_gate             
       mov cx, 0x08
       rep movsb

       mov ax, 0x17e0
       mov es, ax   
       mov di, 0x21*8
       
       mov ax, 0x1860 
       mov ds, ax
       mov si, board_gate             
       mov cx, 0x08
       rep movsb 

       mov ax, 0x17e0
       mov es, ax   
       mov di, 0x2c*8
       
       mov ax, 0x1860 
       mov ds, ax
       mov si, mouse_gate             
       mov cx, 0x08
       rep movsb  

       ;------------------------;  
       mov ax, 0x2040
       mov es, ax
       mov di, 0x00           

       mov ax, 0x1a40
       mov ds, ax
       xor si, si             
       mov cx, 0x400
       rep movsb

   	   ;------------------------;  
       mov ax, 0x2080
       mov es, ax
       mov di, 0x00           

       mov ax, 0x1a80
       mov ds, ax
       xor si, si             
       mov cx, 0x400
       rep movsb

	   ;------------------------;	
	   mov ax, 0x1860
	   mov ds, ax
	   mov byte [packageSize], 0x10
	   mov byte [reserveByte], 0x00
	   mov word [blockCount], 0x200
	   mov word [bufferOffs], 0x00
	   mov word [bufferSegm], 0x8000
	   mov dword [blockNum], 0x40

	   mov ah, 0x42
       mov dl, 0x80
	   mov si, packageSize
	   int 0x13

       ;------------------------;
       mov bx, 0x4118
       mov ax, 0x4f02
       int 0x10 

	   ;------------------------;
	   mov ax, 0x2140
	   mov ds, ax
	   xor bx, bx
	   mov ah, 0x88
	   int 0x15
	   mov [ds:bx], ax	           
           
       cli

       mov ax, 0x1860 
       mov ds, ax
        
       mov word [ds: gdt_size], 0xffff                                            
       lgdt [ds: gdt_size]

       mov word [ds: idt_size], 0x7ff
       lidt [ds: idt_size]

       in al, 0x92                         
       or al, 0000_0010B
       out 0x92, al                                                
                                       
       mov eax, cr0
       or eax, 1
       mov cr0, eax

       jmp dword SYS_SELECTOR : KERNAL_ADDR 


packageSize: db 0
reserveByte: db 0
blockCount:  dw 0
bufferOffs:  dw 0
bufferSegm:  dw 0
blockNum:    dq 0
