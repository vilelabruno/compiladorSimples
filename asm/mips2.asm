.data
	_esp: .asciiz " "
	_ent: .asciiz "\n"
	_const0: .asciiz "Digite o valor de n: "
	_const1: .asciiz "fatorial = "
	n: .word 1
	fat: .word 1
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
	sw $v0, n
#--- CRCT ---
	li $a0 1
#--- ARZG ---
	sw $a0, fat
L1:	nop
#--- CRVG ---
	lw $a0 n
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRCT ---
	li $a0 0
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- CMMA ---
	slt $a0, $a0, $t1
#--- DSVF ---
	beqz $a0, L2
#--- CRVG ---
	lw $a0 fat
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRVG ---
	lw $a0 n
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- MULT ---
	mult $t1, $a0
	mflo $a0
#--- ARZG ---
	sw $a0, fat
#--- CRVG ---
	lw $a0 n
	sw $a0 0($sp)
	addiu $sp $sp -4
#--- CRCT ---
	li $a0 1
	lw $t1 4($sp)
	addiu $sp $sp 4
#--- SUBT ---
	sub $a0, $t1, $a0
#--- ARZG ---
	sw $a0, n
#--- DSVS ---
	j L1
L2:	nop
#--- CRCT (literal) ---
	la $a0 _const1
#--- ESCR ---
	li $v0, 4
	syscall
#--- CRVG ---
	lw $a0 fat
#--- ESCR ---
	li $v0, 1
	syscall
fim:	nop