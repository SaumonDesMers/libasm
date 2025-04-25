; typedef struct s_list
; {
; 	void * data;
; 	struct s_list * next;
; } t_list;

; void ft_list_remove_if(t_list ** begin_list, void * data_ref, int (*cmp)(), void (*free_fct)(void *));

section .text
	global ft_list_remove_if

	extern free

ft_list_remove_if:
	cmp rdi, 0				; test if begin_list is NULL
	je end
	cmp QWORD [rdi], 0		; test if *begin_list is NULL
	je end
	cmp rdx, 0				; test if cmp function is NULL
	je end

	push rbx
	push r12
	push r13
	push r14
	push r15

	mov r12, rdi			; save begin_list
	mov r13, rsi			; save data_ref
	mov r14, rdx			; save cmp function
	mov r15, rcx			; save free function

	mov rbx, [r12]			; get first node ptr

remove_loop_start:
	cmp rbx, 0				; test if node is NULL
	je remove_loop_end

	mov rdi, [rbx]			; get node data
	mov rsi, r13			; get data_ref
	call r14				; call cmp function with current data and data_ref

	cmp eax, 0				; test cmp return value
	jne no_remove			; do not remove if cmp did not return 0

	mov r8, rbx				; save 'current node ptr' to free it later
	push r8					; save 'current node ptr' accross the call
	mov rbx, [rbx + 8]		; get 'current node next ptr'
	mov [r12], rbx			; set 'previous node next ptr' to 'current node next ptr'

	cmp r15, 0				; test if free_fct is NULL
	je no_free_fct			; do not call free_fct if it is NULL

	mov rdi, [r8]			; get 'current node data ptr'
	call r15				; call free_fct on 'current node data ptr'

no_free_fct:

	pop rdi					; restore 'current node ptr'
	call free WRT ..plt		; free the 'current node ptr'

	jmp remove_loop_start

no_remove:

	mov r12, rbx
	add r12, 8				; save the 'previous node next ptr' address
	mov rbx, [r12]			; go to next node

	jmp remove_loop_start

remove_loop_end:

	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx

end:
	ret