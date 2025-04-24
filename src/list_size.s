; typedef struct s_list
; {
; 	void * data;
; 	struct s_list * next;
; } t_list;

; int ft_list_size(t_list * begin_list);

section .text
	global ft_list_size

ft_list_size:
	xor rax, rax		; init counter

size_loop_start:
	cmp rdi, 0			; test if end of list
	je size_loop_end

	inc rax				; increment counter
	mov rdi, [rdi + 8]	; go to next list node

	jmp size_loop_start
size_loop_end:

	ret