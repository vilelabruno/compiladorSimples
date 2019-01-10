
#include "tree.h"
int contaGrau = 0;

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

void mostra(ptno raiz, int nivel){
	ptno p;
	int i;
	for(i = 0; i < nivel; i++)
		printf("..");
	switch(raiz->tipo){
		case 9: 	printf ("texto _const%s\n", raiz->valor); break;
		case 10: 	printf ("programa\n"); break;
		case 11: 	printf ("declaracao de variaveis\n"); break;
		case 12: 	printf ("tipo: %s\n", raiz->valor); break;
		case 13: 	printf ("lista variaveis\n") ; break;
		case 14: 	printf ("lista comandos\n") ; break;
		case 15: 	printf ("leitura\n") ; break;
		case 16: 	printf ("escrita\n"); break;
		case 17: 	printf ("repeticao\n") ; break;
		case 18: 	printf ("selecao\n") ; break;
		case 19: 	printf ("atribuicao\n") ; break;
		case 20: 	printf ("multiplicacao\n") ; break;
		case 21: 	printf ("divisao\n"); break;
		case 22: 	printf ("soma\n") ; break;
		case 23: 	printf ("subtracao\n") ; break;
		case 24: 	printf ("compara maior\n") ; break;
		case 25: 	printf ("compara menor\n") ; break;
		case 26: 	printf ("compara igual\n"); break;
		case 27: 	printf ("conjucao\n") ; break;
		case 28: 	printf ("disjuncao\n") ; break;
		case 29: 	printf ("identificador: %s\n", raiz->valor); break;
		case 30: 	printf ("variavel: %s\n", raiz->valor); break;
		case 31: 	printf ("numero: %s\n", raiz->valor) ; break;
		case 32: 	printf ("verdadeiro\n") ; break;
		case 33: 	printf ("falso\n") ; break;
		case 34: 	printf ("negacao (NAO)\n") ; break;		
	}
	p = raiz->filho;
	while(p) {
		mostra(p, nivel+1);
		p = p->irmao;
	}

}
void geradot(ptno raiz, int nivel){
	ptno p;
	
	p = raiz->filho;

	if (raiz) {
		if (raiz->valor){
			switch(raiz->tipo){
				case 9: 	printf ("\tn%p [label = \"texto | _const%s \"]; \n", raiz, raiz->valor); break;
				case 10: 	printf ("\tn%p [label = \"programa| %s \"]; \n", raiz, raiz->valor); break;
				case 11: 	printf ("\tn%p [label = \"declaracao de variaveis| %s \"]; \n", raiz, raiz->valor); break;
				case 12: 	printf ("\tn%p [label = \"tipo: %s| %s \"]; \n", raiz, raiz->valor); break;
				case 13: 	printf ("\tn%p [label = \"lista variaveis| %s \"]; \n", raiz, raiz->valor); break;
				case 14: 	printf ("\tn%p [label = \"lista comandos| %s \"]; \n", raiz, raiz->valor); break;
				case 15: 	printf ("\tn%p [label = \"leitura| %s \"]; \n", raiz, raiz->valor); break;
				case 16: 	printf ("\tn%p [label = \"escrita| %s \"]; \n", raiz, raiz->valor); break;
				case 17: 	printf ("\tn%p [label = \"repeticao| %s \"]; \n", raiz, raiz->valor); break;
				case 18: 	printf ("\tn%p [label = \"selecao| %s \"]; \n", raiz, raiz->valor); break;
				case 19: 	printf ("\tn%p [label = \"atribuicao| %s \"]; \n", raiz, raiz->valor); break;
				case 20: 	printf ("\tn%p [label = \"multiplicacao| %s \"]; \n", raiz, raiz->valor); break;
				case 21: 	printf ("\tn%p [label = \"divisao| %s \"]; \n", raiz, raiz->valor); break;
				case 22: 	printf ("\tn%p [label = \"soma| %s \"]; \n", raiz, raiz->valor); break;
				case 23: 	printf ("\tn%p [label = \"subtracao| %s \"]; \n", raiz, raiz->valor); break;
				case 24: 	printf ("\tn%p [label = \"compara maior| %s \"]; \n", raiz, raiz->valor); break;
				case 25: 	printf ("\tn%p [label = \"compara menor| %s \"]; \n", raiz, raiz->valor); break;
				case 26: 	printf ("\tn%p [label = \"compara igual| %s \"]; \n", raiz, raiz->valor); break;
				case 27: 	printf ("\tn%p [label = \"conjucao| %s \"]; \n", raiz, raiz->valor); break;
				case 28: 	printf ("\tn%p [label = \"disjuncao| %s \"]; \n", raiz, raiz->valor); break;
				case 29: 	printf ("\tn%p [label = \"identificador: %s\n", raiz->valor); break;
				case 30: 	printf ("\tn%p [label = \"variavel: %s\n", raiz->valor); break;
				case 31: 	printf ("\tn%p [label = \"numero: %s\n", raiz->valor) ; break;
				case 32: 	printf ("\tn%p [label = \"verdadeiro| %s \"]; \n", raiz, raiz->valor); break;
				case 33: 	printf ("\tn%p [label = \"falso| %s \"]; \n", raiz, raiz->valor); break;
				case 34: 	printf ("\tn%p [label = \"negacao (NAO)| %s \"]; \n", raiz, raiz->valor); break;		
			}
			
		}else{
			switch(raiz->tipo){
				case 9: 	printf ("\tn%p [label = \"texto  | \"]; \n", raiz); break;
				case 10: 	printf ("\tn%p [label = \"programa | \"]; \n", raiz); break;
				case 11: 	printf ("\tn%p [label = \"declaracao de variaveis | \"]; \n", raiz); break;
				case 12: 	printf ("\tn%p [label = \"tipo:  | \"]; \n", raiz); break;
				case 13: 	printf ("\tn%p [label = \"lista variaveis | \"]; \n", raiz); break;
				case 14: 	printf ("\tn%p [label = \"lista comandos | \"]; \n", raiz); break;
				case 15: 	printf ("\tn%p [label = \"leitura | \"]; \n", raiz); break;
				case 16: 	printf ("\tn%p [label = \"escrita | \"]; \n", raiz); break;
				case 17: 	printf ("\tn%p [label = \"repeticao | \"]; \n", raiz); break;
				case 18: 	printf ("\tn%p [label = \"selecao | \"]; \n", raiz); break;
				case 19: 	printf ("\tn%p [label = \"atribuicao | \"]; \n", raiz); break;
				case 20: 	printf ("\tn%p [label = \"multiplicacao | \"]; \n", raiz); break;
				case 21: 	printf ("\tn%p [label = \"divisao | \"]; \n", raiz); break;
				case 22: 	printf ("\tn%p [label = \"soma | \"]; \n", raiz); break;
				case 23: 	printf ("\tn%p [label = \"subtracao | \"]; \n", raiz); break;
				case 24: 	printf ("\tn%p [label = \"compara maior | \"]; \n", raiz); break;
				case 25: 	printf ("\tn%p [label = \"compara menor | \"]; \n", raiz); break;
				case 26: 	printf ("\tn%p [label = \"compara igual | \"]; \n", raiz); break;
				case 27: 	printf ("\tn%p [label = \"conjucao | \"]; \n", raiz); break;
				case 28: 	printf ("\tn%p [label = \"disjuncao | \"]; \n", raiz); break;
				case 29: 	printf ("\tn%p [label = \"identificador:  | \"]; \n", raiz); break;
				case 30: 	printf ("\tn%p [label = \"variavel:  | \"]; \n", raiz); break;
				case 31: 	printf ("\tn%p [label = \"numero:  | \"]; \n", raiz); break;
				case 32: 	printf ("\tn%p [label = \"verdadeiro | \"]; \n", raiz); break;
				case 33: 	printf ("\tn%p [label = \"falso | \"]; \n", raiz); break;
				case 34: 	printf ("\tn%p [label = \"negacao (NAO) | \"]; \n", raiz); break;		
			}
		}
	}
	while(p) {
		geradot(p, nivel+1);
		if (p) printf ( "\tn%p -> n%p; \n" , raiz, p);	
		p = p->irmao;
	}

}