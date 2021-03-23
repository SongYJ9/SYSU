org  7c00h                      ; BIOS将把引导扇区加载到0:7C00h处，并开始执行

OffSetOfUserPrg1 equ 8100h      ; 设置用户程序位置

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

judge:
    mov ax,cs
	mov ds,ax                   ; 重置数据段
	mov ss,ax                   
    mov dx, word[c5]
    cmp dx,5
    jz start
    cmp dx,4
    jz start                    ; 回到监控程序
	jmp run 		            ; 继续顺序执行 

start:
	call cls
	mov	ax, cs	                ; 置其他段寄存器值与CS相同
	mov	ds, ax	                ; 数据段
	mov	bp, Message		        ; BP = 当前串的偏移地址
	mov	ax, ds		            ; ES:BP = 串地址
	mov	es, ax		            ; 置ES = DS
	mov	cx, MessageLength       ; CX = 串长（ = 9 ）
	mov	ax, 1301h		        ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 0007h		        ; 页号为 0 (BH = 0) 黑底白字(BL = 07h)
    mov dh, 0		            ; 行号 = 0
	mov	dl, 0			        ; 列号 = 0
	int	10h			            ; BIOS的10h功能：显示一行字符

input:
    mov ah,00h 			        ; 功能号：代表读入键盘输入的ascii码
 	int 16h                     ; BIOS的16h功能：从键盘读入一个字符，读入到 AL 中
    cmp al,'5'                  ; 新建功能：输入 5 跳转到"输入运行顺序"模块
    jz getstr
	cmp al,'1'			        ; 判断越界( 是否 < 1 )
	jl input                    ; 重新输入
	cmp al,'4'                  ; 判断越界( 是否 > 4 )
	jg input                    ; 重新输入
	sub al,'0'-1			    ; 把 AL 转为读取的扇区号（从扇区 2 开始）
	mov byte[index],al

LoadnEx:
    mov word[c5],5        
    mov ax,cs                   ; 段地址：存放数据的内存基地址
    mov es,ax                   ; 设置段地址（不能直接mov es,段地址）
    mov bx, OffSetOfUserPrg1    ; 偏移地址; 存放数据的内存偏移地址
    mov ah,2                    ; 功能号
    mov al,1                    ; 扇区数
    mov dl,0                    ; 驱动器号：软盘为0，硬盘和U盘为80H
    mov dh,0                    ; 磁头号：起始编号为0
    mov ch,0                    ; 柱面号：起始编号为0
    mov cl,byte[index]          ; 起始扇区号：起始编号为1
    int 13H                     ; BIOS的13h功能：读软盘或硬盘上的若干物理扇区到内存的ES:BX处
	call cls                    ; 调用清屏函数
    jmp 800h:100h               ; 跳转至用户程序

getstr:
    call cls
	mov	ax, cs	                ; 置其他段寄存器值与CS相同
	mov	ds, ax	                ; 数据段
	mov	bp, Message2	        ; BP = 当前串的偏移地址
	mov	ax, ds		            ; ES:BP = 串地址
	mov	es, ax		            ; 置ES = DS
	mov	cx, MessageLength2      ; CX = 串长
	mov	ax, 1301h		        ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 0007h		        ; 页号为 0 (BH = 0) 黑底白字(BL = 07h)
    mov dh, 0		            ; 行号 = 0
	mov	dl, 0			        ; 列号 = 0
	int	10h			            ; BIOS的10h功能：显示一行字符
    mov ch,0
incre:
    inc ch
input2:
    mov ah,00h 			        ; 功能号：代表读入键盘输入的ascii码
 	int 16h                     ; BIOS的16h功能：从键盘读入一个字符，读入到 AL 中
    cmp al,'1'			        ; 判断越界( 是否 < 1 )
	jl input2                   ; 重新输入
	cmp al,'4'                  ; 判断越界( 是否 > 4 )
	jg input2                   ; 重新输入
    sub al,'0'-1
    cmp ch,1
    jz save1
    cmp ch,2
    jz save2
    cmp ch,3
    jz save3
    cmp ch,4
    jz save4
save1:
    mov ah,0
    mov word[c1],ax
    jmp incre
save2:
    mov ah,0
    mov word[c2],ax
    jmp incre
save3:
    mov ah,0
    mov word[c3],ax
    jmp incre
save4:
    mov ah,0
    mov word[c4],ax
    mov word[c5],0
	call cls                    ; 调用清屏函数
run:
    inc word[c5]
    mov dx, word[c5]
    cmp dx,1
    jz change1
    cmp dx,2
    jz change2
    cmp dx,3
    jz change3
    cmp dx,4
    jz change4
run2:
    mov byte[index],al
    mov ax,cs                   ; 段地址：存放数据的内存基地址
    mov es,ax                   ; 设置段地址（不能直接mov es,段地址）
    mov bx, OffSetOfUserPrg1    ; 偏移地址; 存放数据的内存偏移地址
    mov ah,2                    ; 功能号
    mov al,1                    ; 扇区数
    mov dl,0                    ; 驱动器号：软盘为0，硬盘和U盘为80H
    mov dh,0                    ; 磁头号：起始编号为0
    mov ch,0                    ; 柱面号：起始编号为0
    mov cl,byte[index]          ; 起始扇区号：起始编号为1
    int 13H                     ; BIOS的13h功能：读软盘或硬盘上的若干物理扇区到内存的ES:BX处
    jmp 800h:100h               ; 跳转至用户程序

change1:
    mov ax,word[c1]
    jmp run2
change2:
    mov ax,word[c2]
    jmp run2
change3:
    mov ax,word[c3]
    jmp run2
change4:
    mov ax,word[c4]
    jmp run2

int20h:
    jmp judge

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

AfterRun:
    jmp $                     ; 无限循环
Message:
    db "Welcome to syj's os, please press 1-4 to run a program, press 5 to input running sequence:"
MessageLength  equ ($-Message)
Message2:
    db "Please input 4 number, from 1 to 4:"
MessageLength2  equ ($-Message2)
      index db '1'
      c1 dw 1
      c2 dw 2
      c3 dw 3
      c4 dw 4
      c5 dw 5
      times 510-($-$$) db 0
      db 0x55,0xaa
