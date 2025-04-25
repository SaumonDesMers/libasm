section .text
	global ft_strcpy

ft_strcpy:
	mov rax, rdi		; save str in rax

loop_start:
	cmp BYTE [rsi], 0	; test end of string
	je loop_end			; while (*src != 0) {
	movsb				; 	*dest++ = *src++
	jmp loop_start		; }
loop_end:

	mov BYTE [rdi], 0	; add null terminator
	ret
