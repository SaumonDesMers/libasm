; typedef struct s_list
; {
; 	void * data;
; 	struct s_list * next;
; } t_list;

; void ft_list_sort(t_list ** begin_list, int (*cmp)());

section .text
	global ft_list_sort

ft_list_sort:
	cmp rdi, 0				; test if begin_list is NULL
	je end
	cmp QWORD [rdi], 0		; ; test if *begin_list is NULL
	je end
	cmp QWORD [rdi + 8], 0	; test if the list has more than one element
	je end
	cmp rsi, 0				; test if cmp function is NULL
	je end

	push rbx
	push r12
	push r13
	push r14
	push r15

	mov r12, rdi			; save begin_list
	mov r13, rsi			; save cmp function

sort_start:
	xor rbx, rbx			; use rbx as a boolean to know if there was a swap
	mov r14, [r12]			; use r14 to iterate over the list

sort_loop_start:
	mov r15, [r14 + 8]		; get next list element
	cmp r15, 0				; test if next element is NULL
	je sort_loop_end

	mov rdi, [r14]
	mov rsi, [r15]
	call r13				; call cmp function with current and next list element

	cmp eax, 0				; test cmp return value
	jle no_swap				; do not swap if current <= next

	; swap the two element
	mov rcx, [r14]
	mov rdx, [r15]
	mov [r14], rdx
	mov [r15], rcx

	mov rbx, 1				; set swap boolean to true

no_swap:

	mov r14, r15			; go to next list node
	jmp sort_loop_start

sort_loop_end:

	cmp rbx, 1				; test if there was a swap
	je sort_start			; start again if there was

	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx

end:
	ret