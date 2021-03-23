	org 0AB00h					; 告诉编译器将程序加载到100h处
	mov ax,cs
	mov ds,ax
	mov ss,ax

Start:
    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test1               ; es:dx=串地址
    mov ah, 01h                 ; 系统调用功能号ah=01h，大写转小写
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
    mov dx, test1               ; es:dx=串地址
    mov ah, 02h                 ; 系统调用功能号ah=02h，小写转大写
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
    mov dx, test1               ; es:dx=串地址
    mov bx, 7                   ; 部分反转，只反转前 7 位
    mov ah, 03h                 ; 系统调用功能号ah=03h，反转
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
    mov dx, test2               ; es:dx=串地址
    mov ah, 04h                 ; 系统调用功能号ah=04h，atoi
    int 21h                     ; ax=转换后的数字

    mov bx, 16388
    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test2               ; es:dx=串地址
    mov ah, 05h                 ; 系统调用功能号ah=05h，itoa
    int 21h                     ; es:dx=转换后的数字字符串
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
    mov dx, test3               ; es:dx=串地址
    mov ah, 06h                 ; 系统调用功能号ah=06h，atoi_2
    int 21h                     ; ax=转换后的数字
    
    mov bx, 46
    mov ax, cs
    mov es, ax                  ; es=cs
    mov dx, test3               ; es:dx=串地址
    mov ah, 07h                 ; 系统调用功能号ah=07h，itoa_2
    int 21h                     ; es:dx=转换后的数字字符串
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
    mov ah, 0                   ; 输入任意键退出
    int 16h
	int 20h						; 检测退出中断
    
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