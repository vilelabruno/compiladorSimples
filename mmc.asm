.data
	_esp: .asciiz " "
	_ent: .asciiz "\n"
	_const0: .asciiz "digite o valor de a: " 
	_const1: .asciiz "digite o valor de b: " 
	_const2: .asciiz "o maior valor eh: " 
	_const3: .asciiz "o maior valor eh: " 
	_const4: .asciiz "digite o valor de b: " 
	_const5: .asciiz "digite o valor de a: " 
	b: .word 1 
	a: .word 1 
.text
	.globl main
main:	nop
	la $a0, _const0
	li $v0, 1
	syscall
	li $v0, 5
	syscall
	sw $v0, a
	la $a0, _const1
	li $v0, 1
	syscall
	li $v0, 5
	syscall
	sw $v0, b
	la $a0, _const2
	li $v0, 1
	syscall
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
	slt $a0, $t1, $a0
	beqz $a0, L1
	li $a0, 0
	j L2
L1:	li $a0, 1
L2:	nop
	beqz $a0, L3
	la $a0, a
	li $v0, 1
	syscall
	j L4
L3:	nop
	la $a0, b
	li $v0, 1
	syscall
L4:	nop
fim:	nop