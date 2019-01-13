
#include "tree.h"
int contaGrau = 0;
int contaGrau2 = 0;
int controlVar = -1;
int contaConstante = 0;
int ls = 0;
ptno criaNo(int tipo, char *valor){
	ptno n = (ptno) malloc (sizeof(struct no));
	n->tipo = tipo;
	n->valor = (char *) malloc (strlen(valor)*sizeof(char)+1);
 	strcpy (n->valor,valor);
	n->filho = NULL;
	n->irmao = NULL;
	return n;
}

void adicionaFilho(ptno pai, ptno filho){

	if(filho){
		if(!pai->filho){
			contaGrau++;
		}
		
		filho->irmao = pai->filho;
		pai->filho = filho;	
	}	
}
void geraconstante(ptno p){
	if (!p) return;
	if(p->tipo == 9) {
		printf("	_const%d: .asciiz %s \n", contaGrau2, p->valor);
		contaGrau2++;
	}
	ptno aux = p;
	while (p->filho){
		geraconstante(p->filho);
		p = p->filho;
	}
	p = aux;
	geraconstante(p->irmao);

}

void geravars(ptno p){
	if (!p) return;
	if(p->tipo == 29 && controlVar == 0) {
		printf("	%s: .word 1 \n", p->valor);
	}
	if(p->tipo == 14){
		printf(".text\n\t.globl main\nmain:	nop\n");
		return;
	}
	if(p->tipo == 11){
		controlVar = 0;
	}

	//printf("%d\n", p->tipo);
	ptno aux = p;
	while (p->filho) {
		geravars(p->filho); 
		p = p->filho;
	}
	p = aux;
	geravars(p->irmao);
}



void geramips(ptno p){
	if ( p == NULL) return;
 	ptno p1 , p2 , p3 ;
 	switch ( p->tipo ) {
 		case 9:
 			printf("_const%d\n", contaConstante++);
 			break;
 		case 30:
 			printf("%s\n", p->valor);
 			break;
 		case 29:
 			printf("%s\n", p->valor);
 			break;
 		case 31:
 			printf("%s\n", p->valor);
 			break;
 		case 10: 
 			p1 = p->filho ;
 			p2 = p1->irmao ;
 			p3 = p2->irmao ;
 			printf(".data\n\t_esp: .asciiz \" \"\n\t_ent: .asciiz \"\\n\"\n");
 			

 			geraconstante(p3);
 			geravars ( p2 ) ;
 			geramips ( p3 ) ;
 			printf ( "fim:	nop" ) ;
 			break ;
 		case 11:
 			p1 = p->filho ;
 			geramips ( p1->irmao ) ;
 			printf ( "\n.text\n\t.globl main\nmain:	nop\n" ) ;
 			break ;
 		case 13:
 			geravars ( p ) ;
 			break ;
 		case 14:
 			p1 = p->filho ;
 			p2 = p1->irmao ;
 			geramips ( p1 ) ;
 			geramips ( p2 ) ;
 			break;
 		case 15:
 			printf("\tli $v0, 5\n\tsyscall\n\tsw $v0, ");// verificar tipo
 			geramips(p->filho);
 			break;
 		case 16:
 			printf("\tla $a0, "); // verificar tipo
 			geramips(p->filho);
 			printf("\tli $v0, 4\n\tsyscall\n");
 			break;
 		case 17:
 			ls++;
 			printf("L%d:	nop\n", ls);
 			empilha(ls);
 			geramips(p->filho);
 			ls++;
 			printf ("\tbeqz $a0, L%d\n", ls); 
 			empilha(ls); 			
 			geramips(p->filho->irmao);
 			ptno aux = desempilha(); 
 			printf("\tj L%d\n", desempilha()); 
 			printf("L%d:	nop\n", aux);
 			break;
 		case 18:
 			geramips(p->filho);
 			ls++;
 			printf("\tbeqz $a0, L%d\n", ls); 
 			empilha(ls);
 			geramips(p->filho->irmao);
 			ls++;
 			printf  ("\tj L%d\n", ls); 
 			printf("L%d:	nop\n", desempilha()); 
 			empilha(ls);
 			geramips(p->filho->irmao->irmao); 
 			printf("L%d:	nop\n", desempilha());
 			break;
 		case 19:
 			if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}

 			geramips( p->filho->irmao);
 			
	 		printf("\tsw $a0, ");
 			geramips( p->filho);
 			break;
/* 		case 19:
 			if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
 				printf("\tli $a0 ");
 			}else if(p->filho->tipo == 29 || p->filho->tipo == 30 ){
 				printf("\tlw $a0 ");
 			}
 			geramips(p->filho);
 			int auxTipo = p->filho->irmao->tipo;
 			if (auxTipo != 9 && auxTipo != 30 && auxTipo != 29 && auxTipo != 31 ){
 			 	printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
 			 	if(p->filho->irmao->tipo == 31){
	 				printf("\tli $a0 ");
 				}else{
 					printf("\tlw $a0 ");
 				}
 			}else{
	 			printf("\tsw $a0, ");
 			}
 			
 			geramips( p->filho->irmao);
 			if (p->filho->irmao->tipo == 14){
 			 	printf("\tsw $a0 4($sp)\n\taddiu $sp $sp 	4\n");
 			}
 			break;*/
 		case 20:
 		 	 if (p->filho->tipo == 31 || p->filho->tipo == 29 || p->filho->tipo == 30 || p->filho->tipo == 9){
 				if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}

 			geramips(p->filho);
			printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
			
 		 	
 		 	if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho->irmao);

			printf("\tlw $t1 4($sp)\n\taddiu $sp $sp 4\n");
 			printf("\tmult $t1, $a0\n\tmflo $a0\n");
 			break;
 		case 21:
 		 	
 		 	if (p->filho->tipo == 31 || p->filho->tipo == 29 || p->filho->tipo == 30 || p->filho->tipo == 9){
 				if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho);
			printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
			
 		 	
 		 	if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho->irmao);

			printf("\tlw $t1 4($sp)\n\taddiu $sp $sp 4\n");
 			printf("\t div $t1, $a0\n\tmflo $a0\n");
 			break;
 		case 22:
 		 	if (p->filho->tipo == 31 || p->filho->tipo == 29 || p->filho->tipo == 30 || p->filho->tipo == 9){
 				if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho);
			printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
			
 		 	if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho->irmao);

			printf("\tlw $t1 4($sp)\n\taddiu $sp $sp 4\n");
 			printf("\tadd $a0, $t1, $a0\n");
 			break;
 		case 23:
 		 	if (p->filho->tipo == 31 || p->filho->tipo == 29 || p->filho->tipo == 30 || p->filho->tipo == 9){
 				if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho);
			printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
			
 		 	if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho->irmao);

			printf("\tlw $t1 4($sp)\n\taddiu $sp $sp 4\n");
 			printf("\tsub $a0, $t1, $a0\n");
 			break;
 		case 24:
 		 	if (p->filho->tipo == 31 || p->filho->tipo == 29 || p->filho->tipo == 30 || p->filho->tipo == 9){
 				if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho);
			printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
			
 		 	if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho->irmao);

			printf("\tlw $t1 4($sp)\n\taddiu $sp $sp 4\n");
 			printf("\tslt $a0, $a0, $t1\n");
 			break;
 		case 25:
 		 	if (p->filho->tipo == 31 || p->filho->tipo == 29 || p->filho->tipo == 30 || p->filho->tipo == 9){
 				if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho);
			printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
			
 		 	if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho->irmao);

			printf("\tlw $t1 4($sp)\n\taddiu $sp $sp 4\n");
 			printf("\tslt $a0, $t1, $a0\n");
 			break;
 		case 26:
 		 	if (p->filho->tipo == 31 || p->filho->tipo == 29 || p->filho->tipo == 30 || p->filho->tipo == 9){
 				if(p->filho->tipo == 31 || p->filho->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho);
			printf("\tsw $a0 0($sp)\n\taddiu $sp $sp -4\n");
			
 		 	if (p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 29 || p->filho->irmao->tipo == 30 || p->filho->irmao->tipo == 9){
 				if(p->filho->irmao->tipo == 31 || p->filho->irmao->tipo == 9 ){
	 				printf("\tli $a0 ");
 				}else{
	 				printf("\tlw $a0 ");
 				}
 			}
 			geramips(p->filho->irmao);

			printf("\tlw $t1 4($sp)\n\taddiu $sp $sp 4\n");
			ls++;
 			empilha(ls);
 			printf("\tbeq $a0, $t1, L%d\n", ls);
 			printf("\tli $a0 0\n");
 			ls++;

 			empilha(ls);
 			printf("\tj L%d\n", ls);
 			printf("L%d:\tli $a0, 1\n", desempilha()-1);

 			printf("L%d:\tnop\n", desempilha()+1);
 			break;
 		case 27:
 		 	
 			geramips(p->filho);
 			ls++;
 			empilha(ls);
 			printf("\tbeqz $a0, L%d\n", ls);
 			printf("\tbeqz $t1, L%d\n", ls);
 			ls++;
 			empilha(ls);
			printf("\tli $a0, 1\n\tj L%d\n", ls);
			printf("L%d:	li $a0, 0\n", desempilha()-1);
			printf("L%d:\tnop\n", desempilha()+1);
			break;
 		case 28:

 		 	
 			geramips(p->filho);
 			ls++;
 			empilha(ls);
 			printf("\tbnez $a0, L%d\n", ls);
 			printf("\tbnez $t1, L%d\n", ls);
 			ls++;
 			empilha(ls);
			printf("\tli $a0, 0\n\tj L%d\n", ls);
			printf("L%d:	li $a0, 1\n", desempilha()-1);
			printf("L%d:\tnop\n", desempilha()+1);
			break;
 		case 32:
 			print("\t1\n");
 			break;
 		case 33:
 			print("\t0\n");
 			break;
 		case 34:
 			geramips(p->filho);
 			ls++;
 			empilha(ls);
 			printf("\tbeqz $a0, L%d\n", ls);
 			ls++;
 			empilha(ls);
			printf("\tli $a0, 0\n\tj L%d\n", ls);
			printf("L%d:	li $a0, 1\n", desempilha()-1);
			printf("L%d:\tnop\n", desempilha()+1);
			break;
 	}

}

void geradot(ptno raiz){
	ptno p;
	
	p = raiz->filho;

	if (raiz) {
		if (raiz->valor){
			switch(raiz->tipo){
				case 9: 	printf ("\tn%p [label = \"<f0>texto | <f1> _const%d \"]; \n", raiz, contaGrau); contaGrau++; break;
				case 10: 	printf ("\tn%p [label = \"<f0>programa | <f1>  \"]; \n", raiz); break;
				case 11: 	printf ("\tn%p [label = \"<f0>declaracao de variaveis | <f1>  \"]; \n", raiz); break;
				case 12: 	printf ("\tn%p [label = \"<f0>tipo | <f1> %s \"]; \n", raiz, raiz->valor); break;
				case 13: 	printf ("\tn%p [label = \"<f0>lista variaveis | <f1>  \"]; \n", raiz); break;
				case 14: 	printf ("\tn%p [label = \"<f0>lista comandos | <f1>  \"]; \n", raiz); break;
				case 15: 	printf ("\tn%p [label = \"<f0>leitura | <f1>  \"]; \n", raiz); break;
				case 16: 	printf ("\tn%p [label = \"<f0>escrita | <f1>  \"]; \n", raiz); break;
				case 17: 	printf ("\tn%p [label = \"<f0>repeticao | <f1>  \"]; \n", raiz); break;
				case 18: 	printf ("\tn%p [label = \"<f0>selecao | <f1>  \"]; \n", raiz); break;
				case 19: 	printf ("\tn%p [label = \"<f0>atribuicao | <f1>  \"]; \n", raiz); break;
				case 20: 	printf ("\tn%p [label = \"<f0>multiplicacao | <f1>  \"]; \n", raiz); break;
				case 21: 	printf ("\tn%p [label = \"<f0>divisao | <f1>  \"]; \n", raiz); break;
				case 22: 	printf ("\tn%p [label = \"<f0>soma | <f1>  \"]; \n", raiz); break;
				case 23: 	printf ("\tn%p [label = \"<f0>subtracao | <f1>  \"]; \n", raiz); break;
				case 24: 	printf ("\tn%p [label = \"<f0>compara maior | <f1>  \"]; \n", raiz); break;
				case 25: 	printf ("\tn%p [label = \"<f0>compara menor | <f1>  \"]; \n", raiz); break;
				case 26: 	printf ("\tn%p [label = \"<f0>compara igual | <f1>  \"]; \n", raiz); break;
				case 27: 	printf ("\tn%p [label = \"<f0>conjucao | <f1>  \"]; \n", raiz); break;
				case 28: 	printf ("\tn%p [label = \"<f0>disjuncao | <f1>  \"]; \n", raiz); break;
				case 29: 	printf ("\tn%p [label = \"<f0>identificador | <f1> %s \"]; \n", raiz, raiz->valor); break;
				case 30: 	printf ("\tn%p [label = \"<f0>variavel | <f1> %s\"]; \n",raiz,  raiz->valor); break;
				case 31: 	printf ("\tn%p [label = \"<f0>numero | <f1> %s\"]; \n", raiz, raiz->valor) ; break;
				case 32: 	printf ("\tn%p [label = \"<f0>verdadeiro | <f1>  \"]; \n", raiz); break;
				case 33: 	printf ("\tn%p [label = \"<f0>falso | <f1>  \"]; \n", raiz); break;
				case 34: 	printf ("\tn%p [label = \"<f0>negacao (NAO) | <f1>  \"]; \n", raiz); break;	
			}
			
		}else{
			switch(raiz->tipo){
				case 9: 	printf ("\tn%p [label = \"texto | <f1> \"]; \n", raiz); break;
				case 10: 	printf ("\tn%p [label = \"programa | <f1> \"]; \n", raiz); break;
				case 11: 	printf ("\tn%p [label = \"declaracao de variaveis | <f1> \"]; \n", raiz); break;
				case 12: 	printf ("\tn%p [label = \"tipo | <f1> \"]; \n", raiz); break;
				case 13: 	printf ("\tn%p [label = \"lista variaveis | <f1> \"]; \n", raiz); break;
				case 14: 	printf ("\tn%p [label = \"lista comandos | <f1> \"]; \n", raiz); break;
				case 15: 	printf ("\tn%p [label = \"leitura | <f1> \"]; \n", raiz); break;
				case 16: 	printf ("\tn%p [label = \"escrita | <f1> \"]; \n", raiz); break;
				case 17: 	printf ("\tn%p [label = \"repeticao | <f1> \"]; \n", raiz); break;
				case 18: 	printf ("\tn%p [label = \"selecao | <f1> \"]; \n", raiz); break;
				case 19: 	printf ("\tn%p [label = \"atribuicao  | <f1> \"]; \n", raiz); break;
				case 20: 	printf ("\tn%p [label = \"multiplicacao | <f1> \"]; \n", raiz); break;
				case 21: 	printf ("\tn%p [label = \"divisao | <f1> \"]; \n", raiz); break;
				case 22: 	printf ("\tn%p [label = \"soma | <f1> \"]; \n", raiz); break;
				case 23: 	printf ("\tn%p [label = \"subtracao | <f1> \"]; \n", raiz); break;
				case 24: 	printf ("\tn%p [label = \"compara maior | <f1> \"]; \n", raiz); break;
				case 25: 	printf ("\tn%p [label = \"compara menor | <f1> \"]; \n", raiz); break;
				case 26: 	printf ("\tn%p [label = \"compara igual | <f1> \"]; \n", raiz); break;
				case 27: 	printf ("\tn%p [label = \"conjucao | <f1> \"]; \n", raiz); break;
				case 28: 	printf ("\tn%p [label = \"disjuncao | <f1> \"]; \n", raiz); break;
				case 29: 	printf ("\tn%p [label = \"identificador | <f1> \"]; \n", raiz); break;
				case 30: 	printf ("\tn%p [label = \"variavel | <f1> \"]; \n", raiz); break;
				case 31: 	printf ("\tn%p [label = \"numero | <f1> \"]; \n", raiz); break;
				case 32: 	printf ("\tn%p [label = \"verdadeiro | <f1> \"]; \n", raiz); break;
				case 33: 	printf ("\tn%p [label = \"falso | <f1> \"]; \n", raiz); break;
				case 34: 	printf ("\tn%p [label = \"negacao (NAO) | <f1> \"]; \n", raiz); break;		
			}
		}
	}
	while(p) {
		geradot(p);
		if (p) printf ( "\tn%p -> n%p; \n" , raiz, p);	
		p = p->irmao;
	}

}