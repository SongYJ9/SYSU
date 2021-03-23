	bits 16
    global LoadnEx
	global cls
	global schar
	extern main
	extern draw
	extern in,qi
	extern toupper,tolower,reverse,atoi,itoa,atoi_2,itoa_2
	OffSetOfUserPrg1 equ 0A100h ; 设置用户程序位置
	
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
	mov ax, 0000h               ; 内存前64k放置的中断向量表，将段寄存器指向该处
    mov es, ax
    mov ax, 21h	                ; 定义21号中断：系统调用
    mov bx, 4
    mul bx
    mov si, ax
    mov ax, int21h
    mov [es:si], ax
    add si, 2
    mov ax, cs
    mov [es:si], ax
	mov ax, 0000h               ; 内存前64k放置的中断向量表，将段寄存器指向该处
    mov es, ax
    mov ax, 22h	                ; 定义22号中断：显示 ouch
    mov bx, 4
    mul bx
    mov si, ax
    mov ax, int22h
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
	mov al, 5                   ; 扇区数
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

schar:
	push ax
	mov ah, 01h					; 功能号，扫描但不等待输入
	int 16h
	jz noschar
	mov word[in],1				; 有输入，赋值为 1
	mov ah, 00h
	int 16h						; 从键盘输入缓冲区中取出输入
	pop ax
	ret
noschar:
	mov word[in],0				; 无输入，赋值为 0
	pop ax
	ret

int20h:
	call save
    call cls
    jmp main
	jmp restart					; 结构对称，实际上该代码不执行

int21h:
	call save
	push ds
    push si                     ; 用si作为内部临时寄存器
    mov si, cs
    mov ds, si                  ; ds = cs
    mov si, ax
    shr si, 8                   ; si = 功能号
    add si, si                  ; si = 2 * 功能号
	sub si, 2
    call [sys_table+si]         ; 系统调用函数
    pop si
    pop ds
	jmp restart					
sys_table:						; 存放功能号与系统调用函数映射的表
    dw sys_1,sys_2,sys_3,sys_4,sys_5,sys_6,sys_7

int22h:
    call save
	mov ax,ouch
	mov bp,ax
    mov cx,len
    mov ax,1301h
    mov bx,000fh
    mov dx,0505h
    int 10h
	jmp restart					

int8h:
	cli							; 屏蔽外部中断
	call save
	push 0
	call draw					; c 模块“数字钟”显示
	push ax
	mov al,20h
	out 20h,al
	out 0A0h,al					; 中断结束
	pop ax
	sti							; 解除屏蔽
	jmp restart

save:
	push ds
	push cs
	pop ds					; ds 指向内核
	pop word[save_ds]		; 保存了原始的 ds ，即用户程序
	pop word[save_cs]		; 保存了 save 返回的地址
	mov word[save_si],si
	mov si,word[qi]			; c 中的 save 结构体
	pop word[si]
	pop word[si+4]
	pop word[si+8]
	mov word[si+12],es		; es 
	push word[save_ds]
	pop word[si+16]			; ds
	mov word[si+20],ss		; ss
	mov word[si+24],ax		; ax
	mov word[si+28],bx		; bx
	mov word[si+32],cx		; cx
	mov word[si+36],dx		; dx
	mov word[si+40],di		; di
	mov word[si+44],bp		; bp
	mov word[si+48],sp		; sp
	push word[save_si]
	pop word[si+52]			; si
	jmp word[save_cs]

restart:
	mov si,[qi]
	mov es,word[si+12]		; es
	mov ss,word[si+20]		; ss
	mov ax,word[si+24]		; ax
	mov bx,word[si+28]		; bx
	mov cx,word[si+32]		; cx
	mov dx,word[si+36]		; dx
	mov di,word[si+40]		; di
	mov bp,word[si+44]		; bp
	mov sp,word[si+48]		; sp
	push word[si+8]
	push word[si+4]
	push word[si]
	push word[si+52]
	push word[si+16]
	pop ds					; ds
	pop si					; si
	iret

sys_1:
    push es					; 传递参数
    push dx					; 传递参数
    call dword toupper
    pop dx					; 丢弃参数
    pop es					; 丢弃参数
    ret

sys_2:
    push es					; 传递参数
    push dx					; 传递参数
    call dword tolower
    pop dx					; 丢弃参数
    pop es					; 丢弃参数
    ret

sys_3:
    mov ax, 0
    push ax					; 传递参数 len
    push bx					; 传递参数 len
    push es					; 传递参数 s
    push dx					; 传递参数 s
    call dword reverse
    pop bx					; 丢弃参数
    pop ax					; 丢弃参数
    pop dx					; 丢弃参数
    pop es					; 丢弃参数
    ret

sys_4:
    push es					; 传递参数
    push dx					; 传递参数
    call dword atoi
    pop dx					; 丢弃参数
    pop es					; 丢弃参数
    ret

sys_5:
    push es					; 传递参数 s
    push dx					; 传递参数 s
    mov ax, 0
    push ax					; 传递参数 val
    push bx					; 传递参数 val
    call dword itoa
    pop bx					; 丢弃参数
    pop ax					; 丢弃参数
    pop dx					; 丢弃参数
    pop es					; 丢弃参数
    ret

sys_6:
    push es					; 传递参数
    push dx					; 传递参数
    call dword atoi_2
    pop dx					; 丢弃参数
    pop es					; 丢弃参数
    ret

sys_7:
    push es					; 传递参数 s
    push dx					; 传递参数 s
    mov ax, 0
    push ax					; 传递参数 val
    push bx					; 传递参数 val
    call dword itoa_2
    pop bx					; 丢弃参数
    pop ax					; 丢弃参数
    pop dx					; 丢弃参数
    pop es					; 丢弃参数
    ret

datadef:
	save_cs dw 0
	save_si dw 0
	save_ds dw 0
	save_pid dw 0
    ouch db 'INT22H', 0
    len equ $-ouch