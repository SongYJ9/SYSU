	bits 16
	extern main
	global find
_start:
	call main
_end:
	jmp $

find:
	db "abbcccddddeeeeesyj",0x00