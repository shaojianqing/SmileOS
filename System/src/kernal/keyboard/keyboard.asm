
[bits 32]

push ds
pushad

mov eax, 00010_000B
mov ds, eax

mov al, 0x61
out 0x20, al
in  al, 0x60

mov esi, 0x20c00
mov ecx, [esi]

mov edi, 0x20c04
mov edx, [edi]

mov ebx, ecx
sub ebx, 2
cmp ebx, edx
je end

mov [edx + 0x20c08], al

cmp edx, 999
jge roll

inc edx
mov [edi], edx
jmp end

roll:
xor edx, edx
mov [edi], edx

end:
popad
pop ds
iretd
