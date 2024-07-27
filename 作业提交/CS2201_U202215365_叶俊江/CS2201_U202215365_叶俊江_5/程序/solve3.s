.global _start

.section .text
_start:
	push 8(%ebp)	//传入pos
	call 0x13dc	//PC相对寻址
	add $4,%esp	//回退4字节
	
	
