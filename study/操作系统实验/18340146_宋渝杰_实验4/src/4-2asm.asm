	bits 16
	extern main
	extern draw
    global LoadnEx
	global cls
	OffSetOfUserPrg1 equ 0A100h  ; �����û�����λ��
	
_start:
	mov ax, cs
	mov ds, ax
	mov ss, ax
    mov ax, 0000h               ; �ڴ�ǰ64k���õ��ж����������μĴ���ָ��ô�
    mov es, ax
    mov ax, 20h	                ; ����20���жϣ����ؼ�س���
    mov bx, 4
    mul bx
    mov si, ax
    mov ax, int20h
    mov [es:si], ax
    add si, 2
    mov ax, cs
    mov [es:si], ax
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
	call main
_end:
	jmp $

LoadnEx:
	push ebp					; ebp��ջ
	mov ebp, esp				; ��Ϊesp�Ƕ�ջָ�룬�޷��ݽ�ʹ�ã����Ե���ebp����ȡ��ջ
	mov ecx, [ebp+8]
	mov ax, cs                  ; �ε�ַ��������ݵ��ڴ����ַ
	mov es, ax                  ; ���öε�ַ������ֱ��mov es,�ε�ַ��
	mov bx, OffSetOfUserPrg1    ; ƫ�Ƶ�ַ; ������ݵ��ڴ�ƫ�Ƶ�ַ
	mov ah, 2                   ; ���ܺ�
	mov al, 1                   ; ������
	mov dl, 0                   ; ���ܺ�
	mov dh, 1                   ; ��ͷ�ţ���ʼ���Ϊ0
	mov ch, 0                   ; ����ţ���ʼ���Ϊ0
	int 13H                     ; BIOS��13h���ܣ������̻�Ӳ���ϵ����������������ڴ��ES:BX��
	call cls                    ; ������������
	jmp OffSetOfUserPrg1
	mov esp, ebp
	pop ebp
	ret

cls:   
    mov bx,0b800h               ; �Դ��ַ 0xb800
    mov es,bx
    mov bx,0
    mov cx,4000                 ; ����ѭ����������*��*2��80*25*2 = 4000�ֽ�
s:
    mov dx,0000h                ; �ڵ�����
    mov [es:bx],dx        
    add bx,2
    loop s                      ; ѭ�� 4000 ��
	ret			                ; ���غ������õ�

int20h:
	; call cls                  ; ������������
    jmp main
	jmp $

int8h:
	cli							; �����ⲿ�ж�
	push cs						; ���� c ģ�麯������
	call draw					; ������������ʾ����
	mov al, 20H
	out 20H, al					; ���ֽ� 20h �� 20h �Ŷ˿����
	out 0a0H, al				; �жϽ�������
	sti							; �ָ��ⲿ�ж�
	iret						; �жϽ�������