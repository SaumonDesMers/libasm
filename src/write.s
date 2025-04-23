extern __errno_location

section .text
	global ft_write

ft_write:
	mov rax, 1						; syscall number for write
	syscall							; call the kernel
	cmp rax, 0						; check if the return value is negative
	jl error 						; if it is, jump to error handling
	ret

error:
	neg rax							; negate rax to get the error code
	mov rdi, rax					; move the error code to rdi to save it
	call __errno_location WRT ..plt	; call __errno_location to get the address of errno
	mov [rax], rdi					; store the error code in errno
	mov rax, -1						; set rax to -1 to indicate an error
	ret
