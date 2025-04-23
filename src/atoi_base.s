section .text
	global ft_atoi_base

ft_atoi_base:

	xor rax, rax			; init return value
	mov rdx, 1				; use rdx to store the sign


	; setup hashtable in the stack
	mov r9, rsp				; use rsp for hashtable start
	mov rcx, 16
hashtable_loop:
	push QWORD 0			; push 8 bytes 16 times to get 128 bytes
	loop hashtable_loop


	; check if arguments are non-NULL
	cmp rdi, 0
	je end
	cmp rsi, 0
	je end

	; check if base is valid, get it's lenght and setup the hashtable
	mov r8, rsi				; use r8 to iterate over the base
	mov cl, 0				; use cl as the base lenght counter
base_loop_start:
	cmp BYTE [r8], 0		; check end of str
	je base_loop_end

	cmp BYTE [r8], 43		; check if the is '+' in the base
	je end
	cmp BYTE [r8], 45		; check if the is '-' in the base
	je end

	mov r10, r9				; get the hashtable start
	mov r12, 0
	mov r12b, BYTE [r8]
	sub r10, r12		; sub the character value to get it's emplacement (hash function)
	cmp BYTE [r10], 0		; check if stored value is zero
	jne end					; if it's not zero, that means there is a duplicated character

	mov BYTE [r10], cl		; store the character emplacement in the base string
	inc BYTE [r10]			; add one to get the one-based indexing

	inc cl
	inc r8					; increment str ptr
	jmp base_loop_start
base_loop_end:

	cmp cl, 2				; check if base has a least 2 character
	jl end


	; ignore leading whitespace
	dec rdi
whitespace_loop_start:
	inc rdi
	cmp BYTE [rdi], 0		; check end of str
	je end

	cmp BYTE [rdi], 9		; '\t'
	je whitespace_loop_start
	cmp BYTE [rdi], 10		; '\n'
	je whitespace_loop_start
	cmp BYTE [rdi], 11		; '\v'
	je whitespace_loop_start
	cmp BYTE [rdi], 12		; '\f'
	je whitespace_loop_start
	cmp BYTE [rdi], 13 		; '\r'
	je whitespace_loop_start
	cmp BYTE [rdi], 32 		; ' '
	je whitespace_loop_start


	; handle sign
sign_loop_start:
	cmp BYTE [rdi], 0		; check end of str
	je end

	cmp BYTE [rdi], '+'		; check if there is a '+'
	je plus
	cmp BYTE [rdi], '-'		; check if there is a '-'
	je minus

	jmp sign_loop_end

minus:						; if there is a '-', inverse the sign
	neg rdx					; negate rdx to reflect number sign
plus:						; if there is a '+' just pass
	inc rdi					; increment str ptr
	jmp sign_loop_start

sign_loop_end:


	; finaly translate the number
number_loop_start:
	cmp BYTE [rdi], 0		; check end of str
	je end

	imul rax, rcx			; multiply the result by the base lenght

	mov r10, r9				; get the hashtable start
	mov r12, 0
	mov r12b, BYTE [rdi]
	sub r10, r12			; sub the character value to get it's emplacement (hash function)
	cmp BYTE [r10], 0		; check if stored value is zero
	je end					; if it's zero, that means this character is not part of the base so it's the end

	add al, BYTE [r10]		; add the next number to the result
	dec rax

	inc rdi
	jmp number_loop_start

end:
	mov rsp, r9				; reset stack pointer
	imul rax, rdx			; apply sign to the number
	ret
