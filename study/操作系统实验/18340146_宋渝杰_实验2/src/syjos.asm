org  7c00h                      ; BIOS���������������ص�0:7C00h��������ʼִ��

OffSetOfUserPrg1 equ 8100h      ; �����û�����λ��

    mov ax, 0000h               ; �ڴ�ǰ64k���õ��ж����������μĴ���ָ��ô�
    mov es, ax
    mov ax, 20h	                ; ����20���жϣ����ؼ�س���
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
	mov ds,ax                   ; �������ݶ�
	mov ss,ax                   
    mov dx, word[c5]
    cmp dx,5
    jz start
    cmp dx,4
    jz start                    ; �ص���س���
	jmp run 		            ; ����˳��ִ�� 

start:
	call cls
	mov	ax, cs	                ; �������μĴ���ֵ��CS��ͬ
	mov	ds, ax	                ; ���ݶ�
	mov	bp, Message		        ; BP = ��ǰ����ƫ�Ƶ�ַ
	mov	ax, ds		            ; ES:BP = ����ַ
	mov	es, ax		            ; ��ES = DS
	mov	cx, MessageLength       ; CX = ������ = 9 ��
	mov	ax, 1301h		        ; AH = 13h�����ܺţ���AL = 01h��������ڴ�β��
	mov	bx, 0007h		        ; ҳ��Ϊ 0 (BH = 0) �ڵװ���(BL = 07h)
    mov dh, 0		            ; �к� = 0
	mov	dl, 0			        ; �к� = 0
	int	10h			            ; BIOS��10h���ܣ���ʾһ���ַ�

input:
    mov ah,00h 			        ; ���ܺţ����������������ascii��
 	int 16h                     ; BIOS��16h���ܣ��Ӽ��̶���һ���ַ������뵽 AL ��
    cmp al,'5'                  ; �½����ܣ����� 5 ��ת��"��������˳��"ģ��
    jz getstr
	cmp al,'1'			        ; �ж�Խ��( �Ƿ� < 1 )
	jl input                    ; ��������
	cmp al,'4'                  ; �ж�Խ��( �Ƿ� > 4 )
	jg input                    ; ��������
	sub al,'0'-1			    ; �� AL תΪ��ȡ�������ţ������� 2 ��ʼ��
	mov byte[index],al

LoadnEx:
    mov word[c5],5        
    mov ax,cs                   ; �ε�ַ��������ݵ��ڴ����ַ
    mov es,ax                   ; ���öε�ַ������ֱ��mov es,�ε�ַ��
    mov bx, OffSetOfUserPrg1    ; ƫ�Ƶ�ַ; ������ݵ��ڴ�ƫ�Ƶ�ַ
    mov ah,2                    ; ���ܺ�
    mov al,1                    ; ������
    mov dl,0                    ; �������ţ�����Ϊ0��Ӳ�̺�U��Ϊ80H
    mov dh,0                    ; ��ͷ�ţ���ʼ���Ϊ0
    mov ch,0                    ; ����ţ���ʼ���Ϊ0
    mov cl,byte[index]          ; ��ʼ�����ţ���ʼ���Ϊ1
    int 13H                     ; BIOS��13h���ܣ������̻�Ӳ���ϵ����������������ڴ��ES:BX��
	call cls                    ; ������������
    jmp 800h:100h               ; ��ת���û�����

getstr:
    call cls
	mov	ax, cs	                ; �������μĴ���ֵ��CS��ͬ
	mov	ds, ax	                ; ���ݶ�
	mov	bp, Message2	        ; BP = ��ǰ����ƫ�Ƶ�ַ
	mov	ax, ds		            ; ES:BP = ����ַ
	mov	es, ax		            ; ��ES = DS
	mov	cx, MessageLength2      ; CX = ����
	mov	ax, 1301h		        ; AH = 13h�����ܺţ���AL = 01h��������ڴ�β��
	mov	bx, 0007h		        ; ҳ��Ϊ 0 (BH = 0) �ڵװ���(BL = 07h)
    mov dh, 0		            ; �к� = 0
	mov	dl, 0			        ; �к� = 0
	int	10h			            ; BIOS��10h���ܣ���ʾһ���ַ�
    mov ch,0
incre:
    inc ch
input2:
    mov ah,00h 			        ; ���ܺţ����������������ascii��
 	int 16h                     ; BIOS��16h���ܣ��Ӽ��̶���һ���ַ������뵽 AL ��
    cmp al,'1'			        ; �ж�Խ��( �Ƿ� < 1 )
	jl input2                   ; ��������
	cmp al,'4'                  ; �ж�Խ��( �Ƿ� > 4 )
	jg input2                   ; ��������
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
	call cls                    ; ������������
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
    mov ax,cs                   ; �ε�ַ��������ݵ��ڴ����ַ
    mov es,ax                   ; ���öε�ַ������ֱ��mov es,�ε�ַ��
    mov bx, OffSetOfUserPrg1    ; ƫ�Ƶ�ַ; ������ݵ��ڴ�ƫ�Ƶ�ַ
    mov ah,2                    ; ���ܺ�
    mov al,1                    ; ������
    mov dl,0                    ; �������ţ�����Ϊ0��Ӳ�̺�U��Ϊ80H
    mov dh,0                    ; ��ͷ�ţ���ʼ���Ϊ0
    mov ch,0                    ; ����ţ���ʼ���Ϊ0
    mov cl,byte[index]          ; ��ʼ�����ţ���ʼ���Ϊ1
    int 13H                     ; BIOS��13h���ܣ������̻�Ӳ���ϵ����������������ڴ��ES:BX��
    jmp 800h:100h               ; ��ת���û�����

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
    mov bx,0b800h               ; �Դ��ַ 0xb800
    mov es,bx
    mov bx,0
    mov cx,4000                 ; ����ѭ����������*��*2��80*25*2 = 4000�ֽ�
s:
    mov dx,0000h                ; �ڵ�����
    mov [es:bx],dx        
    add bx,2
    loop s                      ; ѭ�� 4000 ��
	ret			                ; ���غ������õ�

AfterRun:
    jmp $                     ; ����ѭ��
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
