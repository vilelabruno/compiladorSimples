
#include "tree.h"
int contaGrau = 0;
int contaGrau2 = 0;
int controlVar = -1;
int contaConstante = 0;
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

void geramips(ptno raiz){
	if (!raiz) return;
	if(raiz->tipo == 14) controlVar = 2;
	ptno p;
	int i;
	p = raiz;
	while(p->filho) {
		geramips(p->filho);
		p = p->filho;
	}
	if (controlVar == 2){
		switch(raiz->tipo){
			case 9: 	
				printf ("\tla $a0 _const%d\n", contaGrau2); contaGrau2++; break;
			case 15: 	
				printf ("\tli $v0, 5\n\tsyscall\n\tsw $v0, %s\n", raiz->filho->valor) ; break;
			case 16: 	printf ("\n\tli $v0, 4\n\tsyscall\n"); break;
			case 17: 	printf ("repeticao\n") ; break;
			case 18: 	printf ("selecao\n") ; break;
			case 19: 	printf ("\tsw $a0, %s\n", raiz->filho->valor) ; break;
			case 20: 	printf ("multiplicacao\n") ; break;
			case 21: 	printf ("divisao\n"); break;
			case 22: 	printf ("soma\n") ; break;
			case 23: 	printf ("subtracao\n") ; break;
			case 24: 	printf ("compara maior\n") ; break;
			case 25: 	printf ("compara menor\n") ; break;
			case 26: 	printf ("compara igual\n"); break;
			case 27: 	printf ("conjucao\n") ; break;
			case 28: 	printf ("disjuncao\n") ; break;
			case 31: 	printf ("\tli $a0 %s\n", raiz->valor) ; break;
			case 32: 	printf ("verdadeiro\n") ; break;
			case 33: 	printf ("falso\n") ; break;
			case 34: 	printf ("negacao (NAO)\n") ; break;		
		}
	}

	geramips(raiz->irmao);

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