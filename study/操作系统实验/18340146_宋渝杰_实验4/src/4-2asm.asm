	bits 16
	extern main
	extern draw
    global LoadnEx
	global cls
	OffSetOfUserPrg1 equ 0A100h  ; 设置用户程序位置
	
_start:
	mov ax, cs
	mov ds, ax
	mov ss, ax
    mov ax, 0000h               ; 内存前64k放置的中断向量表，将段寄存器指向该处
    mov es, ax
    mov ax, 20h	                ; 定义20号中断：返回监控程序
    mov bx, 4
    mul bx
    mov si, ax
    mov ax, int20h
    mov [es:si], ax
    add si, 2
    mov ax, cs
    mov [es:si], ax
	mov ax, 0000h               ; 内存前64k放置的中断向量表，将段寄存器指向该处
    mov es, ax
    mov ax, 8h	                ; 定义8号中断：时钟中断
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
	push ebp					; ebp入栈
	mov ebp, esp				; 因为esp是堆栈指针，无法暂借使用，所以得用ebp来存取堆栈
	mov ecx, [ebp+8]
	mov ax, cs                  ; 段地址：存放数据的内存基地址
	mov es, ax                  ; 设置段地址（不能直接mov es,段地址）
	mov bx, OffSetOfUserPrg1    ; 偏移地址; 存放数据的内存偏移地址
	mov ah, 2                   ; 功能号
	mov al, 1                   ; 扇区数
	mov dl, 0                   ; 功能号
	mov dh, 1                   ; 磁头号：起始编号为0
	mov ch, 0                   ; 柱面号：起始编号为0
	int 13H                     ; BIOS的13h功能：读软盘或硬盘上的若干物理扇区到内存的ES:BX处
	call cls                    ; 调用清屏函数
	jmp OffSetOfUserPrg1
	mov esp, ebp
	pop ebp
	ret

cls:   
    mov bx,0b800h               ; 显存地址 0xb800
    mov es,bx
    mov bx,0
    mov cx,4000                 ; 设置循环次数：长*宽*2：80*25*2 = 4000字节
s:
    mov dx,0000h                ; 黑底无字
    mov [es:bx],dx        
    add bx,2
    loop s                      ; 循环 4000 次
	ret			                ; 返回函数调用点

int20h:
	; call cls                  ; 调用清屏函数
    jmp main
	jmp $

int8h:
	cli							; 屏蔽外部中断
	push cs						; 用于 c 模块函数返回
	call draw					; 调用数字钟显示函数
	mov al, 20H
	out 20H, al					; 将字节 20h 从 20h 号端口输出
	out 0a0H, al				; 中断结束命令
	sti							; 恢复外部中断
	iret						; 中断结束返回