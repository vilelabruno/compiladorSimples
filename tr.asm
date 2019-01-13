.data
	_esp: .asciiz " "
	_ent: .asciiz "\n"
	_const0: .asciiz "digite a: " 
	_const1: .asciiz "digite b: " 
	_const2: .asciiz "digite c: " 
	_const3: .asciiz "Nao tem raiz real" 
	_const4: .asciiz "Nao tem raiz real" 
	_const5: .asciiz "Tem uma raiz" 
	_const6: .asciiz "Tem uma raiz" 
	_const7: .asciiz "Tem duas raizes" 
	_const8: .asciiz "Tem duas raizes" 
	_const9: .asciiz "Tem uma raiz" 
	_const10: .asciiz "Tem uma raiz" 
	_const11: .asciiz "Tem duas raizes" 
	_const12: .asciiz "Tem duas raizes" 
	_const13: .asciiz "Nao tem raiz real" 
	_const14: .asciiz "Nao tem raiz real" 
	_const15: .asciiz "Tem uma raiz" 
	_const16: .asciiz "Tem uma raiz" 
	_const17: .asciiz "Tem duas raizes" 
	_const18: .asciiz "Tem duas raizes" 
	_const19: .asciiz "Tem uma raiz" 
	_const20: .asciiz "Tem uma raiz" 
	_const21: .asciiz "Tem duas raizes" 
	_const22: .asciiz "Tem duas raizes" 
	_const23: .asciiz "digite c: " 
	_const24: .asciiz "digite b: " 
	_const25: .asciiz "digite a: " 
	delta: .word 1 
	c: .word 1 
	b: .word 1 
	a: .word 1 
.text
	.globl main
main:	nop
	la $a0, _const0
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, a
	la $a0, _const1
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, b
	la $a0, _const2
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, c
	lw $a0 b
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
	mult $t1, $a0
	mflo $a0
	sw $a0 0($sp)
	addiu $sp $sp -4
	li $a0 4
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 a
	lw $t1 4($sp)
	addiu $sp $sp 4
	mult $t1, $a0
	mflo $a0
	sw $a0 0($sp)
	addiu $sp $sp -4
	lw $a0 c
	lw $t1 4($sp)
	addiu $sp $sp 4
	mult $t1, $a0
	mflo $a0
	lw $t1 4($sp)
	addiu $sp $sp 4
	sub $a0, $t1, $a0
	sw $a0, delta
	lw $a0 delta
	sw $a0 0($sp)
	addiu $sp $sp -4
	li $a0 0
	lw $t1 4($sp)
	addiu $sp $sp 4
	slt $a0, $t1, $a0
	beqz $a0, L1
	la $a0, _const3
	li $v0, 4
	syscall
	j L2
L1:	nop
	lw $a0 delta
	sw $a0 0($sp)
	addiu $sp $sp -4
	li $a0 0
	lw $t1 4($sp)
	addiu $sp $sp 4
	beq $a0, $t1, L3
	li $a0 0
	j L4
L3:	li $a0, 1
L4:	nop
	beqz $a0, L5
	la $a0, _const4
	li $v0, 4
	syscall
	j L6
L5:	nop
	la $a0, _const5
	li $v0, 4
	syscall
L6:	nop
L2:	nop
fim:	nop