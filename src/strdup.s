extern malloc

section .text
	global ft_strdup

ft_strdup:
	push r12				; save r12
	mov r12, rdi			; save str in r12

strlen_start:
	cmp BYTE [rdi], 0		; test end of string
	je strlen_end			; while (str != 0) {
	inc rdi					;   str++
	jmp strlen_start		; }
strlen_end:

	sub rdi, r12			; substract end of string with start of string

	call malloc WRT ..plt
	cmp rax, 0				; test if malloc failed
	je finish				; go to the end if malloc failed

	mov rdx, rax			; use rdx to iterate over dst ptr

copy_start:
	mov r8b, BYTE [r12]
	mov BYTE [rdx], r8b		; copy char

	cmp BYTE [r12], 0		; test end of string
	je copy_end				; end of the copy if end of string
	inc rdx					; increment dst ptr
	inc r12					; increment src ptr
	jmp copy_start			; continue the copy
copy_end:

finish:
	pop r12					; restore r12
	ret