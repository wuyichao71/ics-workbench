	.file	"asm-impl.c"
	.text
	.p2align 4,,15
	.globl	asm_add
	.type	asm_add, @function
asm_add:
.LFB0:
	.cfi_startproc
	movq	%rdi, %rax
#APP
# 6 "asm-impl.c" 1
	addq %rsi, %rax;
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE0:
	.size	asm_add, .-asm_add
	.p2align 4,,15
	.globl	asm_popcnt
	.type	asm_popcnt, @function
asm_popcnt:
.LFB1:
	.cfi_startproc
	xorl	%edx, %edx
	movl	%edx, %esi
#APP
# 23 "asm-impl.c" 1
	.POPCNT_BEGIN:;cmpl $64, %esi;jge .POPCNT_RET;movl %esi, %ecx;movq %rdi, %rax;shrq %cl, %rax;andl $1, %eax;testq %rax, %rax;je .POPCNT_INCR;incl %edx;.POPCNT_INCR:;incl %esi;jmp .POPCNT_BEGIN;.POPCNT_RET:;
# 0 "" 2
#NO_APP
	movl	%edx, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	asm_popcnt, .-asm_popcnt
	.p2align 4,,15
	.globl	asm_memcpy
	.type	asm_memcpy, @function
asm_memcpy:
.LFB2:
	.cfi_startproc
	testq	%rdx, %rdx
	movq	%rdi, %rax
	je	.L44
	leaq	16(%rdi), %rcx
	cmpq	%rcx, %rsi
	leaq	16(%rsi), %rcx
	setnb	%dil
	cmpq	%rcx, %rax
	setnb	%cl
	orb	%cl, %dil
	je	.L14
	cmpq	$22, %rdx
	jbe	.L14
	movq	%rsi, %rdi
	leaq	-1(%rdx), %r8
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	negq	%rdi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	andl	$15, %edi
	leaq	15(%rdi), %rcx
	cmpq	%rcx, %r8
	jb	.L15
	testq	%rdi, %rdi
	je	.L16
	movzbl	(%rsi), %ecx
	cmpq	$1, %rdi
	movb	%cl, (%rax)
	je	.L17
	movzbl	1(%rsi), %ecx
	cmpq	$2, %rdi
	movb	%cl, 1(%rax)
	je	.L18
	movzbl	2(%rsi), %ecx
	cmpq	$3, %rdi
	movb	%cl, 2(%rax)
	je	.L19
	movzbl	3(%rsi), %ecx
	cmpq	$4, %rdi
	movb	%cl, 3(%rax)
	je	.L20
	movzbl	4(%rsi), %ecx
	cmpq	$5, %rdi
	movb	%cl, 4(%rax)
	je	.L21
	movzbl	5(%rsi), %ecx
	cmpq	$6, %rdi
	movb	%cl, 5(%rax)
	je	.L22
	movzbl	6(%rsi), %ecx
	cmpq	$7, %rdi
	movb	%cl, 6(%rax)
	je	.L23
	movzbl	7(%rsi), %ecx
	cmpq	$8, %rdi
	movb	%cl, 7(%rax)
	je	.L24
	movzbl	8(%rsi), %ecx
	cmpq	$9, %rdi
	movb	%cl, 8(%rax)
	je	.L25
	movzbl	9(%rsi), %ecx
	cmpq	$10, %rdi
	movb	%cl, 9(%rax)
	je	.L26
	movzbl	10(%rsi), %ecx
	cmpq	$11, %rdi
	movb	%cl, 10(%rax)
	je	.L27
	movzbl	11(%rsi), %ecx
	cmpq	$12, %rdi
	movb	%cl, 11(%rax)
	je	.L28
	movzbl	12(%rsi), %ecx
	cmpq	$13, %rdi
	movb	%cl, 12(%rax)
	je	.L29
	movzbl	13(%rsi), %ecx
	cmpq	$15, %rdi
	movb	%cl, 13(%rax)
	jne	.L30
	movzbl	14(%rsi), %ecx
	movl	$15, %r8d
	movb	%cl, 14(%rax)
	movl	$15, %ecx
	.p2align 4,,10
	.p2align 3
.L8:
	movq	%rdx, %rbp
	leaq	(%rsi,%rdi), %r11
	xorl	%r9d, %r9d
	subq	%rdi, %rbp
	xorl	%r10d, %r10d
	addq	%rax, %rdi
	movq	%rbp, %rbx
	shrq	$4, %rbx
	.p2align 4,,10
	.p2align 3
.L10:
	movdqa	(%r11,%r9), %xmm0
	addq	$1, %r10
	movups	%xmm0, (%rdi,%r9)
	addq	$16, %r9
	cmpq	%r10, %rbx
	ja	.L10
	movq	%rbp, %rdi
	andq	$-16, %rdi
	addq	%rdi, %rcx
	addl	%edi, %r8d
	cmpq	%rdi, %rbp
	je	.L5
.L7:
	movslq	%r8d, %r8
	addq	$1, %r8
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L31:
	movq	%rdi, %r8
.L12:
	movzbl	(%rsi,%rcx), %edi
	cmpq	%r8, %rdx
	movb	%dil, (%rax,%rcx)
	leaq	1(%r8), %rdi
	movq	%r8, %rcx
	ja	.L31
.L5:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	.cfi_restore_state
	movl	$1, %ecx
	movl	$1, %r8d
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L6:
	movzbl	(%rsi,%rcx), %edi
	movb	%dil, (%rax,%rcx)
	addq	$1, %rcx
	cmpq	%rcx, %rdx
	jne	.L6
	rep ret
	.p2align 4,,10
	.p2align 3
.L44:
	rep ret
	.p2align 4,,10
	.p2align 3
.L18:
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	.cfi_offset 6, -16
	movl	$2, %ecx
	movl	$2, %r8d
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L15:
	xorl	%r8d, %r8d
	xorl	%ecx, %ecx
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L19:
	movl	$3, %ecx
	movl	$3, %r8d
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L20:
	movl	$4, %ecx
	movl	$4, %r8d
	jmp	.L8
.L23:
	movl	$7, %ecx
	movl	$7, %r8d
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L21:
	movl	$5, %ecx
	movl	$5, %r8d
	jmp	.L8
.L22:
	movl	$6, %ecx
	movl	$6, %r8d
	jmp	.L8
.L16:
	xorl	%ecx, %ecx
	xorl	%r8d, %r8d
	jmp	.L8
.L24:
	movl	$8, %ecx
	movl	$8, %r8d
	jmp	.L8
.L25:
	movl	$9, %ecx
	movl	$9, %r8d
	jmp	.L8
.L26:
	movl	$10, %ecx
	movl	$10, %r8d
	jmp	.L8
.L27:
	movl	$11, %ecx
	movl	$11, %r8d
	jmp	.L8
.L28:
	movl	$12, %ecx
	movl	$12, %r8d
	jmp	.L8
.L29:
	movl	$13, %ecx
	movl	$13, %r8d
	jmp	.L8
.L30:
	movl	$14, %r8d
	movl	$14, %ecx
	jmp	.L8
	.cfi_endproc
.LFE2:
	.size	asm_memcpy, .-asm_memcpy
	.p2align 4,,15
	.globl	asm_setjmp
	.type	asm_setjmp, @function
asm_setjmp:
.LFB3:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_setjmp@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3:
	.size	asm_setjmp, .-asm_setjmp
	.p2align 4,,15
	.globl	asm_longjmp
	.type	asm_longjmp, @function
asm_longjmp:
.LFB4:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	longjmp@PLT
	.cfi_endproc
.LFE4:
	.size	asm_longjmp, .-asm_longjmp
	.ident	"GCC: (SUSE Linux) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
