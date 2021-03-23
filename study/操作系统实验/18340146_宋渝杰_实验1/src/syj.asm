	org 07c00h			; ���߱�������������ص�7c00h��
	mov ax, cs			; ȡ����ζε�ַ����ʱӦ��Ϊ0
	mov ds, ax			; �����ݶ������ε�ַָ����ͬ��ַ
	mov es, ax			; �ø��Ӷ�es�����ε�ַָ����ͬ��ַ
	call DispStr		; ����DispStr����
	jmp $				; ����ѭ����$ ��ʾ�����ǰ��ָ���ַ

DispStr:                				; ����DispStr����ʾһ���ַ���
    
const:
	Dn_Rt equ 1                 		; D-Down,U-Up,R-right,L-Left
	Up_Rt equ 2
	Up_Lt equ 3
	Dn_Lt equ 4
	delay equ 50000			; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
	ddelay equ 580			; ��ʱ���ӳټ���,���ڿ��ƻ�����ٶ�
code:
	org 7c00h			; ������ص�100h������������COM/7c00H������������
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
	mov ax,0B800h			; �ı������Դ���ʼ��ַ
	mov es,ax				; GS = B800h
	mov byte[char],'@'
	mov dx,25
	mov ch,1
loop1:
	dec word[count]			; �ݼ���������
	jnz loop1				; >0����ת;
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
	jz change1			; ���dh=0����ch=16������ת��change1������ɫ
	jmp show

change1:
	mov ch,1			; ������ɫ
	jmp show
change2:
	mov byte[char],'A'			; ������ĸ
	jmp show2

show:	
	xor ax,ax               			; �����Դ��ַ
	mov ax,word[x]
	mov bx,80
	mul bx
	add ax,word[y]
	mov bx,2
	mul bx
	mov bx,ax
	mov ah,ch			; 0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
	inc byte[char]			; ��ʾ���ַ�ASCII��++
	mov dl,91	
	mov cl,byte[char]			; cl=��ʾ���ַ�ASCII��
	sub dl,cl				; dl-cl
	jz change2			; ���dl=0����cl=91������ת��change2�����ַ�
show2:
	mov al,byte[char]			; AL = ��ʾ�ַ�ֵ��Ĭ��ֵΪ20h=�ո����
	mov [es:bx],ax  			; ��ʾ�ַ���ASCII��ֵ
	jmp loop1
end:
	jmp $                   			; ֹͣ��������ѭ�� 
	
datadef:	
	name db "18340146 syj"		; ���Ͻ���ʾ���ַ���
	count dw delay
	dcount dw ddelay
	rdul db Dn_Rt           		; �������˶�
	x    dw 18
	y    dw 0
	char db '@'
	color db 01h
	
times   510-($-$$)  db  0  		; ���ʣ��ռ� $$��ʾ�ó�������section�Ŀ�ʼ��ַ
                           				; �˴�Ϊ7c00h
dw  0xaa55