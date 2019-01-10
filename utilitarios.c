/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
* Limites das estruturas
*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

#define TAM_TSIMB 100 /*Tamanho da tabela de símbolos*/
#define TAM_PSEMA 100 /*Tamanho da pilha semântica*/

/*Variáveis Globais*/

int TOPO_TSIMB = 0;
int TOPO_PSEMA = 0;
int ROTULO     = 0;
int CONTA_VARS = 0;
int CONTA_QUOTE = 0;
int GRAU_TREE = 0;
int POS_SIMB;
int aux;
int numLinha = 1;
char atomo[30];



char * itoa (int value, char *result, int base){
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void ERRO (char *msg, ...) {
	char formato [255];
	va_list arg;
	va_start (arg, msg);
	sprintf (formato, "\n%d: ", numLinha);
	strcat (formato, msg);
	strcat (formato, "\n\n");
	printf("\nERRO no programa");
	vprintf (formato, arg);
	va_end (arg);
	exit (1);
}

/*-----------------------------------------+
|				Tabela de Símbolos		   |
+------------------------------------------*/

struct elem_tab_simbolos{
	char id[30];
	int desloca;
} TSIMB [TAM_TSIMB], elem_tab;

/*-----------------------------------------+
|	Pilha Semântica			   |
+------------------------------------------*/

int PSEMA[TAM_PSEMA];

/*------------------------------------------+
|	Função que BUSCA um símbolo na tabela 	|
|   de símbolos. Retorna -1 se o símbolo	|
|   não está na tabela. Retorna i, onde i é 	|
| 	o índice do símbolo na tabela, se ele	|	
|   estiver na tabela.					    |
+------------------------------------------*/

int busca_simbolo (char *ident){
	int i = TOPO_TSIMB-1;
	for (;strcmp(TSIMB[i].id, ident) && i >=0; i--);
	return i;
}

/*------------------------------------------+
|	Função que INSERE um símbolo na tabela 	|
|   de símbolos. 							|
|   Se já existe um símbolo com mesmo nome  	|
| 	e mesmo nível, uma mensagem de erro é	|	
|   apresentada e o programa é interrompido 	|
+------------------------------------------*/

void insere_simbolo (struct elem_tab_simbolos *elem){
	if (TOPO_TSIMB == TAM_TSIMB) {
		ERRO ("OVERFLOW - tabela de simbolos");
	} else {
		POS_SIMB = busca_simbolo (elem->id);
		if (POS_SIMB != -1) {
			ERRO ("Identificador [%s] duplicado", elem->id);
		}
		TSIMB [TOPO_TSIMB] = *elem;
		TOPO_TSIMB++;
	}
}

/*------------------------------------------+
|	Função de inserção de uma variável  |
|	na tabela de símbolos		    |
+------------------------------------------*/

void insere_variavel (char *ident){
	strcpy (elem_tab.id, ident);
	elem_tab.desloca = CONTA_VARS;
	insere_simbolo (&elem_tab);
}

/*-----------------------------------------------+
|	Rotinas para manutenção da pilha semântica|
+------------------------------------------------*/

void empilha (int n){
	if (TOPO_PSEMA == TAM_PSEMA){
		ERRO ("OVERFLOW - Pilha Semântica");
	}
	PSEMA[TOPO_PSEMA++] = n;
}

int desempilha (){
	if (TOPO_PSEMA == 0){
		ERRO ("UNDERFLOW - Pilha Semantica");
	}
	return PSEMA[--TOPO_PSEMA];
}

enum {
	texto 				= 9, 
	programa 				= 10, 
	declaracao_variaveis 	= 11, 
	tipo 					= 12, 
	lista_de_variaveis 		= 13, 
	lista_de_comandos 		= 14, 
	leitura 				= 15, 
	escrita 				= 16, 
	repeticao 				= 17, 
	selecao 				= 18, 
	atribuicao 				= 19, 
	multiplicacao 			= 20, 
	divisao 				= 21, 
	soma 					= 22, 
	subtracao 				= 23, 
	maior 					= 24, 
	menor 					= 25, 
	igual 					= 26, 
	conjuncao 				= 27, 
	disjuncao 				= 28, 
	identificador 			= 29, 
	variavel 				= 30, 
	numero 					= 31, 
	verdadeiro 				= 32, 
	falso 					= 33, 
	nao 					= 34  
};
