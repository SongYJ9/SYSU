	bits 16
	org 7c00H
start:
	mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax

    mov ax, 0000h               ; �ڴ�ǰ64k���õ��ж����������μĴ���ָ��ô�
    mov es, ax
    mov ax, 8h	                ; ����8���жϣ�ʱ���ж�
    mov bx, 4
    mul bx
    mov si, ax
    mov ax, int8h
    mov [es:si], ax
    add si, 2
    mov ax, cs
    mov [es:si], ax

	mov ax,msg
	mov bp,ax
    mov cx,length
    mov ax,1301h
    mov bx,008ch
    mov dx,0
    int 10h
	jmp $

int8h:
	cli							; �����ⲿ�ж�
	pusha						; ͨ�üĴ���ѹջ
	push eax
	call draw					; ���÷������ת����
	mov al, 20H
	out 20H, al					; ���ֽ� 20h �� 20h �Ŷ˿����
	out 0a0H, al				; �жϽ�������
	pop eax
	popa						; ͨ�üĴ�����ջ
	sti							; �ָ��ⲿ�ж�
	iret						; �жϽ�������

draw:
	mov	ax,0B800h						; �ı������Դ���ʼ��ַ
	mov	gs,ax							; GS = B800h
	mov ah,0Fh							; 0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
	mov al,byte[bar]					; AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո����
	mov [gs:((80*24+79)*2)],ax
	cmp byte[bar],'|'
	je lslash
	cmp byte[bar],'/'
	je hslash
	cmp byte[bar],'-'
	je rslash
	cmp byte[bar],'\'
	je sslash
lslash:
	mov byte[bar],'/'
	ret
hslash:
	mov byte[bar],'-'
	ret
rslash:
	mov byte[bar],'\'
	ret
sslash:
	mov byte[bar],'|'
	ret

datadef:
	bar db '|'

msg:
	db "Welcome to syj's os."
length  equ ($-msg)