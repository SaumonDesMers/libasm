section .text
	global ft_strlen

ft_strlen:
	mov rax, rdi		;save str in rax

loop_start:
	cmp BYTE [rdi], 0	;test end of string
	je loop_end			;while (str != 0) {
	inc rdi				;	str++
	jmp loop_start		;}
loop_end:

	sub rdi, rax		;substract end of string with start of string
	mov rax, rdi		;move result in rax
	ret
