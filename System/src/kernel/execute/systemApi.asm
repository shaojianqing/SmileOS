
global firstApi

firstApi:
	push ebp
	mov ebp, esp
	sub esp, 4
	mov edx, [ebp+8]
	mov [esp], edx
	call 0x20:0x00 
	mov esp, ebp
	pop ebp
	ret
