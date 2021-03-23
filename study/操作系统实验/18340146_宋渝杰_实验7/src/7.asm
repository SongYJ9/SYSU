	bits 16
	extern cmain
start:
	mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
	call dword cmain
end:
	mov ah, 0
	int 16h
	int 20h