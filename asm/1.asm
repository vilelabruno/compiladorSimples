.data
	_esp: .asciiz " "
	_ent: .asciiz "\n"
	_const0: .asciiz "a? "
	_const1: .asciiz "b? "
	_const2: .asciiz "O MDC = "
	a: .word 1
	b: .word 1
.text
	.globl main
main:	nop
#--- CRCT (literal) ---
	la $a0 _const0
#--- ESCR ---
	li $v0, 4
	syscall
#--- LEIA ---
	li $v0, 5
	syscall
	sw $v0, a
#--- CRCT (literal) ---
	la $a0 _const1
#--- ESCR ---
	li $v0, 4
	syscall
#--- LEIA ---
	li $v0, 5
	syscall
	sw $v0, b
L1:	nop
#--- CRVG ---
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- CMIG ---
	beq $a0, $t1, L2
	li $a0, 0
	j L3
L2:	li $a0, 1
L3:	nop
#--- NEGA ---
	beqz $a0, L4
	li $a0, 0
	j L5
L4:	li $a0, 1
L5:	nop
#--- DSVF ---
	beqz $a0, L6
#--- CRVG ---
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- CMMA ---
	slt $a0, $a0, $t1
#--- DSVF ---
	beqz $a0, L7
#--- CRVG ---
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- SUBT ---
	sub $a0, $t1, $a0
#--- ARZG ---
	sw $a0, a
#--- DSVS ---
	j L8
L7:	nop
#--- CRVG ---
	lw $a0 b
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 a
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- SUBT ---
	sub $a0, $t1, $a0
#--- ARZG ---
	sw $a0, b
L8:	nop
#--- DSVS ---
	j L1
L6:	nop
#--- CRCT (literal) ---
	la $a0 _const2
#--- ESCR ---
	li $v0, 4
	syscall
#--- CRVG ---
	lw $a0 a
#--- ESCR ---
	li $v0, 1
	syscall
fim:	nop
