	bits 16
	org 7c00H
start:
	mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax

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

	mov ax,msg
	mov bp,ax
    mov cx,length
    mov ax,1301h
    mov bx,008ch
    mov dx,0
    int 10h
	jmp $

int8h:
	cli							; 屏蔽外部中断
	pusha						; 通用寄存器压栈
	push eax
	call draw					; 调用风火轮旋转函数
	mov al, 20H
	out 20H, al					; 将字节 20h 从 20h 号端口输出
	out 0a0H, al				; 中断结束命令
	pop eax
	popa						; 通用寄存器出栈
	sti							; 恢复外部中断
	iret						; 中断结束返回

draw:
	mov	ax,0B800h						; 文本窗口显存起始地址
	mov	gs,ax							; GS = B800h
	mov ah,0Fh							; 0000：黑底、1111：亮白字（默认值为07h）
	mov al,byte[bar]					; AL = 显示字符值（默认值为20h=空格符）
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