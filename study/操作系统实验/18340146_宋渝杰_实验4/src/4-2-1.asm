	bits 16
	org 7c00H
start:
	mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax

	mov ax, 0000h               ; �ڴ�ǰ 64k ���õ��ж����������μĴ���ָ��ô�
    mov es, ax
 	mov ax, 8h	                ; ���� 8 ���жϣ�ʱ���ж�
    mov bx, 4
 	mul bx						; *4����ȡƫ�Ƶ�ַ
    mov si, ax
 	mov ax, int8h
    mov [es:si], ax				; ����ʱ���ж�������ƫ�Ƶ�ַ
 	add si, 2					; +2����ȡ�жϺ�����ڵ�ַ
    mov ax, cs
    mov [es:si], ax				; ����ʱ���ж������Ķε�ַ = CS

	mov ax,msg
	mov bp,ax
    mov cx,length
    mov ax,1301h
    mov bx,008ch
    mov dx,0
    int 10h
	jmp $

int8h:
	cli							; �����ⲿ�ж�
	pusha						; ͨ�üĴ���ѹջ
	push eax
	call draw					; ���÷������ת����
	mov al, 20H
	out 20H, al					; ���ֽ� 20h �� 20h �Ŷ˿����
	out 0a0H, al				; �жϽ�������
	pop eax
	popa						; ͨ�üĴ�����ջ
	sti							; �ָ��ⲿ�ж�
	iret						; �жϽ�������

draw:
	inc byte[count]
	cmp byte[count],18				; ��ʱ����ÿ����ʾһ�ε�Ч��
	jne end
	mov byte[count],0
	inc byte[num1]					; ���롱��λ��++
	cmp byte[num1],10				; ��λ������ 10 ��ʮλ��++
	jne show
change1:
	mov byte[num1],0				; ���á��롱��λ��
	inc byte[num2]					; ���롱ʮλ��++
	cmp byte[num2],6				; ʮλ������ 6 �򡰷֡���λ��++
	jne show
change2:
	mov byte[num2],0				; ���á��롱ʮλ��
	inc byte[num3]					; ���֡���λ��++
	cmp byte[num3],10				; ��λ������ 10 �򡰷֡�ʮλ��++
	jne show 
change3:
	mov byte[num3],0				; ���á��֡���λ��
	inc byte[num4]					; ���֡�ʮλ��++
	cmp byte[num4],6				; ʮλ������ 6 ������
	jne show
change4:
	mov byte[num4],0				; ���á��֡�ʮλ��
show:
	mov	ax,0B800h					; �ı������Դ���ʼ��ַ
	mov	gs,ax						; GS = B800h
	mov ah,0Fh						; 0000���ڵס�1111�������֣�Ĭ��ֵΪ07h��
	mov al,byte[num4]				
	add al,48
	mov [gs:((80*24+75)*2)],ax		; ������֡�ʮλ��
	mov al,byte[num3]				
	add al,48
	mov [gs:((80*24+76)*2)],ax		; ������֡���λ��
	mov al,':'						
	mov [gs:((80*24+77)*2)],ax		; �����:��
	mov al,byte[num2]				
	add al,48
	mov [gs:((80*24+78)*2)],ax		; ������롱ʮλ��
	mov al,byte[num1]				
	add al,48
	mov [gs:((80*24+79)*2)],ax		; ������롱��λ��
end:
	ret

datadef:
	count db 0						; ��ʱ
	num1 db 0						; ���롱��λ��
	num2 db 0						; ���롱ʮλ��
	num3 db 0						; ���֡���λ��
	num4 db 0						; ���֡�ʮλ��

msg:
	db "Welcome to syj's os."
length  equ ($-msg)