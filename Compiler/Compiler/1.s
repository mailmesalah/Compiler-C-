	.data
newline: .asciiz "\n"
	.text
	.globl main
main:
	li $fp, 0x7ffffffc
	#    

	# loadI 0  r_N'
	li $t0, 0
	sw $t0, 0($fp)

	# loadI 0  r_SQRT'
	li $t0, 0
	sw $t0, -4($fp)

	# readint   r_N
	li $v0, 5
	syscall
	add $t0, $v0, $zero
	sw $t0, -8($fp)

	# exit   
	li $v0, 10
	syscall

