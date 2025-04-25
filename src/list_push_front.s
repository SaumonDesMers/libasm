; typedef struct s_list
; {
; 	void * data;
; 	struct s_list * next;
; } t_list;

; void ft_list_push_front(t_list ** begin_list, void * data);

section .text
	global ft_list_push_front

	extern malloc

ft_list_push_front:
	cmp rdi, 0				; end if begin_list is NULL
	je end

	push r12
	mov r12, rdi			; save rdi
	push r13
	mov r13, rsi			; save rsi

	mov rdi, 16				; size of t_list is 16
	call malloc WRT ..plt	; call malloc(16)

	mov rsi, r13			; restore rsi
	pop r13
	mov rdi, r12			; restore rdi
	pop r12

	cmp rax, 0				; check if malloc failed
	je end

	mov [rax], rsi			; set data ptr
	mov r8, [rdi]
	mov [rax + 8], r8		; set next ptr

	mov [rdi], rax			; set new begin_list

end:
	ret
