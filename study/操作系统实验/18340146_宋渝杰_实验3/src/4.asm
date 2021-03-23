	org 0A100h					; ���߱�������������ص�100h��
	mov ax,cs
	mov ds,ax
	mov ss,ax

const:
	Dn_Rt equ 1                 ; D-Down,U-Up,R-right,L-Left
	Up_Rt equ 2
	Up_Lt equ 3
	Dn_Lt equ 4
	delay equ 50000				; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
	ddelay equ 580				; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
	cou equ 100
code:
	xor ax,ax
	mov ax,cs
	mov es,ax					; ES = 0
	mov ds,ax					; DS = CS
	mov ax,0B800h				; �ı������Դ���ʼ��ַ
	mov gs,ax                   ; GS = B800h
	mov ax,name
	mov bp,ax
	mov cx,Length
	mov ax,01301h
	mov bx,008ch
	mov dx,0
	int 10h

start:
	mov ax,0B800h				; �ı������Դ���ʼ��ַ
	mov es,ax					; GS = B800h
	mov byte[char],'@'
	mov dx,25
	mov ch,1

loop1:
	
	dec word[count]				; �ݼ���������
	jnz loop1					; >0����ת;
	mov word[count],delay
	dec word[dcount]			; �ݼ���������
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
	mov ax,78
	sub ax,bx
	jz  dr2dl
	jmp show

dr2ur:
	mov word[x],23
	mov byte[rdul],Up_Rt	
	jmp change

dr2dl:
	mov word[y],77
	mov byte[rdul],Dn_Lt	
	jmp change

UpRt:
	dec word[x]
	inc word[y]
	mov bx,word[y]
	mov ax,78
	sub ax,bx
	jz  ur2ul
	mov bx,word[x]
	mov ax,14
	sub ax,bx
	jz  ur2dr
	jmp show

ur2ul:
	mov word[y],77
	mov byte[rdul],Up_Lt	
	jmp change

ur2dr:
	mov word[x],16
	mov byte[rdul],Dn_Rt	
	jmp change
	
UpLt:
	dec word[x]
	dec word[y]
	mov bx,word[x]
	mov ax,14
	sub ax,bx
	jz  ul2dl
	mov bx,word[y]
	mov ax,39
	sub ax,bx
	jz  ul2ur
	jmp show

ul2dl:
	mov word[x],16
	mov byte[rdul],Dn_Lt	
	jmp change

ul2ur:
	mov word[y],41
	mov byte[rdul],Up_Rt	
	jmp change

DnLt:
	inc word[x]
	dec word[y]
	mov bx,word[y]
	mov ax,39
	sub ax,bx
	jz  dl2dr
	mov bx,word[x]
	mov ax,25
	sub ax,bx
	jz  dl2ul
	jmp show

dl2dr:
	mov word[y],41
	mov byte[rdul],Dn_Rt	
	jmp change
	
dl2ul:
	mov word[x],23
	mov byte[rdul],Up_Lt	
	jmp change

change:
	inc ch						; ch++
	mov dh,16
	sub dh,ch					; dh-ch
	jz change1					; ���dh=0����ch=16������ת��change1������ɫ
	jmp show

change1:
	mov ch,1					; ������ɫ
	jmp show
change2:
	mov byte[char],'A'			; ������ĸ
	jmp show2

show:	
	xor ax,ax              		; �����Դ��ַ
	mov ax,word[x]
	mov bx,80
	mul bx
	add ax,word[y]
	mov bx,2
	mul bx
	mov bx,ax
	mov ah,ch					; 0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
	inc byte[char]				; ��ʾ���ַ�ASCII��++
	mov dl,91	
	mov cl,byte[char]			; cl=��ʾ���ַ�ASCII��
	sub dl,cl					; dl-cl
	jz change2					; ���dl=0����cl=91������ת��change2�����ַ�
show2:
	mov al,byte[char]			; AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո����
	mov [es:bx],ax  			; ��ʾ�ַ���ASCII��ֵ
	dec word[count2]
	mov dx,word[count2]
	cmp dx,0
	jz end
	jmp loop1
end:
	int 20h						; ����˳��ж�
	jmp $
	
name:
	db "18340146 syj"		; ���Ͻ���ʾ���ַ���
Length  equ ($-name)
	count dw delay
	dcount dw ddelay
	count2 dw cou
	rdul db Dn_Rt           	; �������˶�
	x   dw 16
	y   dw 40
	char db '@'
	color db 01h

	times   512-($-$$)  db  0  	; ���ʣ��ռ� $$��ʾ�ó�������section�Ŀ�ʼ��ַ