.data
	_esp: .asciiz " "
	_ent: .asciiz "\n"
	_const0: .asciiz "digite a: "
	_const1: .asciiz "digite b: "
	_const2: .asciiz "digite c: "
	_const3: .asciiz "Nao tem raiz real"
	_const4: .asciiz "Tem uma raiz"
	_const5: .asciiz "Tem duas raizes"
	a: .word 1
	b: .word 1
	c: .word 1
	delta: .word 1
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
#--- LEIA ---
	li $v0, 5
	syscall
	sw $v0, c
#--- CRVG ---
	lw $a0 b
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 b
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- MULT ---
	mult $t1, $a0
	mflo $a0
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRCT ---
	li $a0 4
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 a
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- MULT ---
	mult $t1, $a0
	mflo $a0
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 c
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- MULT ---
	mult $t1, $a0
	mflo $a0
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- SUBT ---
	sub $a0, $t1, $a0
#--- ARZG ---
	sw $a0, delta
#--- CRVG ---
	lw $a0 delta
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRCT ---
	li $a0 0
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- CMME ---
	slt $a0, $t1, $a0
#--- DSVF ---
	beqz $a0, L1
#--- CRCT (literal) ---
	la $a0 _const3
#--- ESCR ---
	li $v0, 4
	syscall
#--- DSVS ---
	j L2
L1:	nop
#--- CRVG ---
	lw $a0 delta
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRCT ---
	li $a0 0
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- CMIG ---
	beq $a0, $t1, L3
	li $a0, 0
	j L4
L3:	li $a0, 1
L4:	nop
#--- DSVF ---
	beqz $a0, L5
#--- CRCT (literal) ---
	la $a0 _const4
#--- ESCR ---
	li $v0, 4
	syscall
#--- DSVS ---
	j L6
L5:	nop
#--- CRCT (literal) ---
	la $a0 _const5
#--- ESCR ---
	li $v0, 4
	syscall
L6:	nop
L2:	nop
fim:	nop