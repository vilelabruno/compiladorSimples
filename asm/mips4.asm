.data
	_esp: .asciiz " "
	_ent: .asciiz "\n"
	_const0: .asciiz "digite o valor de a: "
	_const1: .asciiz "digite o valor de b: "
	_const2: .asciiz "o maior valor eh: "
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
#--- CRCT (literal) ---
	la $a0 _const2
#--- ESCR ---
	li $v0, 4
	syscall
#--- CRVG ---
	lw $a0 a
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- CMME ---
	slt $a0, $t1, $a0
#--- NEGA ---
	beqz $a0, L1
	li $a0, 0
	j L2
L1:	li $a0, 1
L2:	nop
#--- DSVF ---
	beqz $a0, L3
#--- CRVG ---
	lw $a0 a
#--- ESCR ---
	li $v0, 1
	syscall
#--- DSVS ---
	j L4
L3:	nop
#--- CRVG ---
	lw $a0 b
#--- ESCR ---
	li $v0, 1
	syscall
L4:	nop
fim:	nop