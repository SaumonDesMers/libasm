section .text
	global ft_strcmp

ft_strcmp:

loop_start:
	cmp BYTE [rdi], 0	;if (*s1 == 0)
	je finish			;	goto finish
	cmpsb				;if (*s1++ == *s2++)
	je loop_start		;	goto loop_start

	dec rdi				;s1--
	dec rsi				;s2--

finish:
	xor rax, rax		;rax = 0
	mov al, [rdi]		;set al to *s1 for substraction
	sub al, [rsi]		;al = *s1 - *s2
	movsx eax, al		;carry the sign from 8 bits to 32 bits
	ret
