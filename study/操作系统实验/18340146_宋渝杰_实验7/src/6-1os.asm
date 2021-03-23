	bits 16
	monitorr equ 7e00H
	org 7c00H
start:
	mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
	mov ax,msg
	mov bp,ax
    mov cx,length
    mov ax,1301h
    mov bx,008ch
    mov dx,0
    int 10h

	mov ah, 0
	int 16H
load:
	mov ax, 0
	mov es, ax
	mov bx, monitorr
	mov ah, 2
	mov al, 17
	mov dl, 0
	mov dh, 0
	mov ch, 0
	mov cl, 2
	int 13H
	jmp monitorr

msg:
	db "Enter any to enter syj's os."
length  equ ($-msg)