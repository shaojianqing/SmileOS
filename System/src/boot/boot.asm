
LOADER_START           equ               0x0000

LOADER_SEGMENT         equ               0x1860	   
	
           [bits 16]

	   jmp start
	   db 'Shaojianqing OS.Developed By Shaojianqing Since ' 
	   db '2013-02-10.This Operating System Is Based On Modern'
	   db 'x86 CPU Architecture.Has GUI Interface, Time Sharing'
           db 'Process Management Method And Other Features!'	 

start:     mov ax, 0x7c0
	   mov ds, ax
	   mov byte [packageSize], 0x10
	   mov byte [reserveByte], 0x00
	   mov word [blockCount], 0x20
	   mov word [bufferOffs], 0x00
	   mov word [bufferSegm], 0x1860
	   mov dword [blockNum], 0x01

	   mov ah, 0x42
           mov dl, 0x80
	   mov si, packageSize
	   int 0x13

	   jmp LOADER_SEGMENT : LOADER_START  

packageSize: db 0
reserveByte: db 0
blockCount:  dw 0
bufferOffs:  dw 0
bufferSegm:  dw 0
blockNum:    dq 0
 
times 510-($-$$) db 0
           db 0x55,0xaa
