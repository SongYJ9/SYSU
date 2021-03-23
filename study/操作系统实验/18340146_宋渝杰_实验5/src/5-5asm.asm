	bits 16
    global LoadnEx
	global cls
	global schar
	extern main
	extern draw
	extern in,qi
	extern toupper,tolower,reverse,atoi,itoa,atoi_2,itoa_2
	OffSetOfUserPrg1 equ 0A100h ; �����û�����λ��
	
_start:
	mov ax, cs
	mov ds, ax
	mov ss, ax
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
	mov ax, 0000h               ; �ڴ�ǰ64k���õ��ж����������μĴ���ָ��ô�
    mov es, ax
    mov ax, 8h	                ; ����8���жϣ�ʱ���ж�
    mov bx, 4
    mul bx
    mov si, ax
    mov ax, int8h
    mov [es:si], ax
    add si, 2
    mov ax, cs
    mov [es:si], ax
	mov ax, 0000h               ; �ڴ�ǰ64k���õ��ж����������μĴ���ָ��ô�
    mov es, ax
    mov ax, 21h	                ; ����21���жϣ�ϵͳ����
    mov bx, 4
    mul bx
    mov si, ax
    mov ax, int21h
    mov [es:si], ax
    add si, 2
    mov ax, cs
    mov [es:si], ax
	mov ax, 0000h               ; �ڴ�ǰ64k���õ��ж����������μĴ���ָ��ô�
    mov es, ax
    mov ax, 22h	                ; ����22���жϣ���ʾ ouch
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
	push ebp					; ebp��ջ
	mov ebp, esp				; ��Ϊesp�Ƕ�ջָ�룬�޷��ݽ�ʹ�ã����Ե���ebp����ȡ��ջ
	mov ecx, [ebp+8]
	mov ax, cs                  ; �ε�ַ��������ݵ��ڴ����ַ
	mov es, ax                  ; ���öε�ַ������ֱ��mov es,�ε�ַ��
	mov bx, OffSetOfUserPrg1    ; ƫ�Ƶ�ַ; ������ݵ��ڴ�ƫ�Ƶ�ַ
	mov ah, 2                   ; ���ܺ�
	mov al, 5                   ; ������
	mov dl, 0                   ; ���ܺ�
	mov dh, 1                   ; ��ͷ�ţ���ʼ���Ϊ0
	mov ch, 0                   ; ����ţ���ʼ���Ϊ0
	int 13H                     ; BIOS��13h���ܣ������̻�Ӳ���ϵ����������������ڴ��ES:BX��
	call cls                    ; ������������
	jmp OffSetOfUserPrg1
	mov esp, ebp
	pop ebp
	ret

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

schar:
	push ax
	mov ah, 01h					; ���ܺţ�ɨ�赫���ȴ�����
	int 16h
	jz noschar
	mov word[in],1				; �����룬��ֵΪ 1
	mov ah, 00h
	int 16h						; �Ӽ������뻺������ȡ������
	pop ax
	ret
noschar:
	mov word[in],0				; �����룬��ֵΪ 0
	pop ax
	ret

int20h:
	call save
    call cls
    jmp main
	jmp restart					; �ṹ�Գƣ�ʵ���ϸô��벻ִ��

int21h:
	call save
	push ds
    push si                     ; ��si��Ϊ�ڲ���ʱ�Ĵ���
    mov si, cs
    mov ds, si                  ; ds = cs
    mov si, ax
    shr si, 8                   ; si = ���ܺ�
    add si, si                  ; si = 2 * ���ܺ�
	sub si, 2
    call [sys_table+si]         ; ϵͳ���ú���
    pop si
    pop ds
	jmp restart					
sys_table:						; ��Ź��ܺ���ϵͳ���ú���ӳ��ı�
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
	cli							; �����ⲿ�ж�
	call save
	push 0
	call draw					; c ģ�顰�����ӡ���ʾ
	push ax
	mov al,20h
	out 20h,al
	out 0A0h,al					; �жϽ���
	pop ax
	sti							; �������
	jmp restart

save:
	push ds
	push cs
	pop ds					; ds ָ���ں�
	pop word[save_ds]		; ������ԭʼ�� ds �����û�����
	pop word[save_cs]		; ������ save ���صĵ�ַ
	mov word[save_si],si
	mov si,word[qi]			; c �е� save �ṹ��
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
    push es					; ���ݲ���
    push dx					; ���ݲ���
    call dword toupper
    pop dx					; ��������
    pop es					; ��������
    ret

sys_2:
    push es					; ���ݲ���
    push dx					; ���ݲ���
    call dword tolower
    pop dx					; ��������
    pop es					; ��������
    ret

sys_3:
    mov ax, 0
    push ax					; ���ݲ��� len
    push bx					; ���ݲ��� len
    push es					; ���ݲ��� s
    push dx					; ���ݲ��� s
    call dword reverse
    pop bx					; ��������
    pop ax					; ��������
    pop dx					; ��������
    pop es					; ��������
    ret

sys_4:
    push es					; ���ݲ���
    push dx					; ���ݲ���
    call dword atoi
    pop dx					; ��������
    pop es					; ��������
    ret

sys_5:
    push es					; ���ݲ��� s
    push dx					; ���ݲ��� s
    mov ax, 0
    push ax					; ���ݲ��� val
    push bx					; ���ݲ��� val
    call dword itoa
    pop bx					; ��������
    pop ax					; ��������
    pop dx					; ��������
    pop es					; ��������
    ret

sys_6:
    push es					; ���ݲ���
    push dx					; ���ݲ���
    call dword atoi_2
    pop dx					; ��������
    pop es					; ��������
    ret

sys_7:
    push es					; ���ݲ��� s
    push dx					; ���ݲ��� s
    mov ax, 0
    push ax					; ���ݲ��� val
    push bx					; ���ݲ��� val
    call dword itoa_2
    pop bx					; ��������
    pop ax					; ��������
    pop dx					; ��������
    pop es					; ��������
    ret

datadef:
	save_cs dw 0
	save_si dw 0
	save_ds dw 0
	save_pid dw 0
    ouch db 'INT22H', 0
    len equ $-ouch