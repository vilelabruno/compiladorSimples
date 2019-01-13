.data
	_esp: .asciiz " "
	_ent: .asciiz "\n"
	_const0: .asciiz "a? " 
	_const1: .asciiz "b? " 
	_const2: .asciiz "O MDC = " 
	_const3: .asciiz "O MDC = " 
	_const4: .asciiz "b? " 
	_const5: .asciiz "a? " 
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
L1:	nop
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
	beq $a0, $t1, L2
	li $a0 0
	j L3
L2:	li $a0, 1
L3:	nop
	beqz $a0, L4
	li $a0, 0
	j L5
L4:	li $a0, 1
L5:	nop
	beqz $a0, L6
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
	slt $a0, $a0, $t1
	beqz $a0, L7
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
	sub $a0, $t1, $a0
	sw $a0, a
	j L8
L7:	nop
	lw $a0 b
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 a
	lw $t1 4($sp)
	addiu $sp $sp 4
	sub $a0, $t1, $a0
	sw $a0, b
L8:	nop
	j L1
L6:	nop
	la $a0, _const2
	li $v0, 1
	syscall
	la $a0, a
	li $v0, 1
	syscall
fim:	nop