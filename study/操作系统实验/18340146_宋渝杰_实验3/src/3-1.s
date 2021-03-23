	.file	"3-1.c"
	.code16gcc
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	3
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	4
	.comm	c,4,4
	.text
	.globl	cmain
	.type	cmain, @function
cmain:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	b, %edx
	movl	a, %eax
	subl	$8, %esp
	pushl	%edx
	pushl	%eax
	call	f
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	cmain, .-cmain
	.globl	f
	.type	f, @function
f:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, c
	movl	$2, -4(%ebp)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	f, .-f
	.ident	"GCC: (GNU) 7.1.0"
