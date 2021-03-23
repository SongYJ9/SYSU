	bits 16
	org 7c00H
start:
	mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax

	mov ax, 0000h               ; 内存前 64k 放置的中断向量表，将段寄存器指向该处
    mov es, ax
 	mov ax, 8h	                ; 定义 8 号中断：时钟中断
    mov bx, 4
 	mul bx						; *4，获取偏移地址
    mov si, ax
 	mov ax, int8h
    mov [es:si], ax				; 设置时钟中断向量的偏移地址
 	add si, 2					; +2，获取中断函数入口地址
    mov ax, cs
    mov [es:si], ax				; 设置时钟中断向量的段地址 = CS

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
	inc byte[count]
	cmp byte[count],18				; 延时，起到每秒显示一次的效果
	jne end
	mov byte[count],0
	inc byte[num1]					; “秒”个位数++
	cmp byte[num1],10				; 个位数超过 10 则十位数++
	jne show
change1:
	mov byte[num1],0				; 重置“秒”个位数
	inc byte[num2]					; “秒”十位数++
	cmp byte[num2],6				; 十位数超过 6 则“分”个位数++
	jne show
change2:
	mov byte[num2],0				; 重置“秒”十位数
	inc byte[num3]					; “分”个位数++
	cmp byte[num3],10				; 个位数超过 10 则“分”十位数++
	jne show 
change3:
	mov byte[num3],0				; 重置“分”个位数
	inc byte[num4]					; “分”十位数++
	cmp byte[num4],6				; 十位数超过 6 则重置
	jne show
change4:
	mov byte[num4],0				; 重置“分”十位数
show:
	mov	ax,0B800h					; 文本窗口显存起始地址
	mov	gs,ax						; GS = B800h
	mov ah,0Fh						; 0000：黑底、1111：亮白字（默认值为07h）
	mov al,byte[num4]				
	add al,48
	mov [gs:((80*24+75)*2)],ax		; 输出“分”十位数
	mov al,byte[num3]				
	add al,48
	mov [gs:((80*24+76)*2)],ax		; 输出“分”个位数
	mov al,':'						
	mov [gs:((80*24+77)*2)],ax		; 输出“:”
	mov al,byte[num2]				
	add al,48
	mov [gs:((80*24+78)*2)],ax		; 输出“秒”十位数
	mov al,byte[num1]				
	add al,48
	mov [gs:((80*24+79)*2)],ax		; 输出“秒”个位数
end:
	ret

datadef:
	count db 0						; 延时
	num1 db 0						; “秒”个位数
	num2 db 0						; “秒”十位数
	num3 db 0						; “分”个位数
	num4 db 0						; “分”十位数

msg:
	db "Welcome to syj's os."
length  equ ($-msg)