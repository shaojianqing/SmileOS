  
	[bits 32]
	
	push ds
	pushad

	mov eax, 00010_000B	
	mov ds, eax
	
	mov al, 0x64
	out 0xa0, al
	mov al, 0x62
	out 0x20, al
	in  al, 0x60

	mov dl,al

	mov esi,0x21000+12		;if(free==0) return
	cmp dword [esi],0
	je end

	mov ebx,[0x21000]
	add ebx,0x21000+20
	mov [ebx],dl			;buffer->buf[buffer->p] = data;

	add dword [0x21000],1           ;buffer->p++;

	mov ebx,[0x21000+8]
	cmp ebx,[0x21000]
	jne  NotAddP
	mov dword [0x21000],0

NotAddP:
	sub dword [0x21000+12],1
	jmp end

				
end:	popad 
        pop ds		
        iretd
