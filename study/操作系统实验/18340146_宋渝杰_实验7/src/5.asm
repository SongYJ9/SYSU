	org 0AB00h					; ���߱�������������ص�100h��
	mov ax,cs
	mov ds,ax
	mov ss,ax

Start:
    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test1               ; es:dx=����ַ
    mov ah, 01h                 ; ϵͳ���ù��ܺ�ah=01h����дתСд
    int 21h
    mov ax, sys1
	mov bp, ax
    mov cx, len5
    mov ax, 1301h
    mov bx, 0004h
    mov dx, 0000h
    int 10h
    mov ax, test1
	mov bp, ax
    mov cx, len1
    mov ax, 1301h
    mov bx, 0004h
    mov dx, 000bh
    int 10h

    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test1               ; es:dx=����ַ
    mov ah, 02h                 ; ϵͳ���ù��ܺ�ah=02h��Сдת��д
    int 21h
    mov ax, sys2
	mov bp, ax
    mov cx, len5
    mov ax, 1301h
    mov bx, 000bh
    mov dx, 0200h
    int 10h
    mov ax, test1
	mov bp, ax
    mov cx, len1
    mov ax, 1301h
    mov bx, 000bh
    mov dx, 020bh
    int 10h

    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test1               ; es:dx=����ַ
    mov bx, 7                   ; ���ַ�ת��ֻ��תǰ 7 λ
    mov ah, 03h                 ; ϵͳ���ù��ܺ�ah=03h����ת
    int 21h
    mov ax, sys3
	mov bp, ax
    mov cx, len5
    mov ax, 1301h
    mov bx, 000ch
    mov dx, 0400h
    int 10h
    mov ax, test1
	mov bp, ax
    mov cx, len1
    mov ax, 1301h
    mov bx, 000ch
    mov dx, 040bh
    int 10h

    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test2               ; es:dx=����ַ
    mov ah, 04h                 ; ϵͳ���ù��ܺ�ah=04h��atoi
    int 21h                     ; ax=ת���������

    mov bx, 16388
    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test2               ; es:dx=����ַ
    mov ah, 05h                 ; ϵͳ���ù��ܺ�ah=05h��itoa
    int 21h                     ; es:dx=ת����������ַ���
    mov ax, sys4
	mov bp, ax
    mov cx, len5
    mov ax, 1301h
    mov bx, 000dh
    mov dx, 0600h
    int 10h
    mov ax, test2
	mov bp, ax
    mov cx, len2
    mov ax, 1301h
    mov bx, 000dh
    mov dx, 060bh
    int 10h
    
    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test3               ; es:dx=����ַ
    mov ah, 06h                 ; ϵͳ���ù��ܺ�ah=06h��atoi_2
    int 21h                     ; ax=ת���������
    
    mov bx, 46
    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test3               ; es:dx=����ַ
    mov ah, 07h                 ; ϵͳ���ù��ܺ�ah=07h��itoa_2
    int 21h                     ; es:dx=ת����������ַ���
    mov ax, sys5
	mov bp, ax
    mov cx, len5
    mov ax, 1301h
    mov bx, 000eh
    mov dx, 0800h
    int 10h
    mov ax, test3
	mov bp, ax
    mov cx, len3
    mov ax, 1301h
    mov bx, 000eh
    mov dx, 080bh
    int 10h

    mov ax, mess
	mov bp, ax
    mov cx, len4
    mov ax, 1301h
    mov bx, 0007h
    mov dx, 0a0bh
    int 10h    
    mov ah, 0                   ; ����������˳�
    int 16h
	int 20h						; ����˳��ж�
    
data:
    test1 db 'AbCdEfGSyj', 0
    len1 equ $-test1
    test2 db '16388', 0
    len2 equ $-test2
    test3 db '101110', 0
    len3 equ $-test3
    mess db 'Enter any to return', 0
    len4 equ $-mess
    sys1 db 'syscall_1', 0
    sys2 db 'syscall_2', 0
    sys3 db 'syscall_3', 0
    sys4 db 'syscall_5', 0
    sys5 db 'syscall_7', 0
    len5 equ $-sys5