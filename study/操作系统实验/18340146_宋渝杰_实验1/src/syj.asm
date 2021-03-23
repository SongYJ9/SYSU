	org 07c00h			; 告诉编译器将程序加载到7c00h处
	mov ax, cs			; 取代码段段地址，此时应该为0
	mov ds, ax			; 让数据段与代码段地址指向相同地址
	mov es, ax			; 让附加段es与代码段地址指向相同地址
	call DispStr		; 调用DispStr例程
	jmp $				; 无限循环，$ 表示编译后当前行指令地址

DispStr:                				; 例程DispStr，显示一行字符串
    
const:
	Dn_Rt equ 1                 		; D-Down,U-Up,R-right,L-Left
	Up_Rt equ 2
	Up_Lt equ 3
	Dn_Lt equ 4
	delay equ 50000			; 计时器延迟计数,用于控制画框的速度
	ddelay equ 580			; 计时器延迟计数,用于控制画框的速度
code:
	org 7c00h			; 程序加载到100h，可用于生成COM/7c00H引导扇区程序
	mov ax,cs
	mov es,ax				; ES = 0
	mov ds,ax			; DS = CS
	mov es,ax				; ES = CS
	mov ax,name
	mov bp,ax
	mov cx,12
	mov ax,01301h
	mov bx,008ch
	mov dl,0
	int 10h
start:
	mov ax,0B800h			; 文本窗口显存起始地址
	mov es,ax				; GS = B800h
	mov byte[char],'@'
	mov dx,25
	mov ch,1
loop1:
	dec word[count]			; 递减计数变量
	jnz loop1				; >0：跳转;
	mov word[count],delay
	dec word[dcount]			; 递减计数变量
	jnz loop1
	mov word[count],delay
	mov word[dcount],ddelay
	mov al,1
	cmp al,byte[rdul]
	jz  DnRt
	mov al,2
	cmp al,byte[rdul]
	jz  UpRt
	mov al,3
	cmp al,byte[rdul]
	jz  UpLt
	mov al,4
	cmp al,byte[rdul]
	jz  DnLt
	jmp $	
	
DnRt:
	inc word[x]
	inc word[y]
	mov bx,word[x]
	mov ax,25
	sub ax,bx
	jz  dr2ur
	mov bx,word[y]
	mov ax,80
	sub ax,bx
	jz  dr2dl
	jmp show

dr2ur:
	mov word[x],23
	mov byte[rdul],Up_Rt	
	jmp change

dr2dl:
	mov word[y],78
	mov byte[rdul],Dn_Lt	
	jmp change

UpRt:
	dec word[x]
	inc word[y]
	mov bx,word[y]
	mov ax,80
	sub ax,bx
	jz  ur2ul
	mov bx,word[x]
	mov ax,-1
	sub ax,bx
	jz  ur2dr
	jmp show

ur2ul:
	mov word[y],78
	mov byte[rdul],Up_Lt	
	jmp change

ur2dr:
	mov word[x],1
	mov byte[rdul],Dn_Rt	
	jmp change
	
UpLt:
	dec word[x]
	dec word[y]
	mov bx,word[x]
	mov ax,-1
	sub ax,bx
	jz  ul2dl
	mov bx,word[y]
	mov ax,-1
	sub ax,bx
	jz  ul2ur
	jmp show

ul2dl:
	mov word[x],1
	mov byte[rdul],Dn_Lt	
	jmp change

ul2ur:
	mov word[y],1
	mov byte[rdul],Up_Rt	
	jmp change

DnLt:
	inc word[x]
	dec word[y]
	mov bx,word[y]
	mov ax,-1
	sub ax,bx
	jz  dl2dr
	mov bx,word[x]
	mov ax,25
	sub ax,bx
	jz  dl2ul
	jmp show

dl2dr:
	mov word[y],1
	mov byte[rdul],Dn_Rt	
	jmp change
	
dl2ul:
	mov word[x],23
	mov byte[rdul],Up_Lt	
	jmp change

change:
	inc ch				; ch++
	mov dh,16
	sub dh,ch				; dh-ch
	jz change1			; 如果dh=0（即ch=16），跳转到change1重置颜色
	jmp show

change1:
	mov ch,1			; 重置颜色
	jmp show
change2:
	mov byte[char],'A'			; 重置字母
	jmp show2

show:	
	xor ax,ax               			; 计算显存地址
	mov ax,word[x]
	mov bx,80
	mul bx
	add ax,word[y]
	mov bx,2
	mul bx
	mov bx,ax
	mov ah,ch			; 0000：黑底、1111：亮白字（默认值为07h）
	inc byte[char]			; 显示的字符ASCII码++
	mov dl,91	
	mov cl,byte[char]			; cl=显示的字符ASCII码
	sub dl,cl				; dl-cl
	jz change2			; 如果dl=0（即cl=91），跳转到change2重置字符
show2:
	mov al,byte[char]			; AL = 显示字符值（默认值为20h=空格符）
	mov [es:bx],ax  			; 显示字符的ASCII码值
	jmp loop1
end:
	jmp $                   			; 停止画框，无限循环 
	
datadef:	
	name db "18340146 syj"		; 左上角显示的字符串
	count dw delay
	dcount dw ddelay
	rdul db Dn_Rt           		; 向右下运动
	x    dw 18
	y    dw 0
	char db '@'
	color db 01h
	
times   510-($-$$)  db  0  		; 填充剩余空间 $$表示该程序所在section的开始地址
                           				; 此处为7c00h
dw  0xaa55