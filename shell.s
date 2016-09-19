	.file	"shell.c"
	.text
	.globl	error
	.type	error, @function
error:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movabsq	$8245935278387129921, %rax
	movq	%rax, -32(%rbp)
	movabsq	$7161690017614620704, %rax
	movq	%rax, -24(%rbp)
	movabsq	$44634042997, %rax
	movq	%rax, -16(%rbp)
	movl	$0, -8(%rbp)
	movw	$0, -4(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rdx
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$2, %edi
	call	write
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	error, .-error
	.section	.rodata
.LC0:
	.string	"mysh> "
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
.L3:
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L3
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
