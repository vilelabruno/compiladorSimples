%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "tree.c"
#include "utilitarios.c"
#include "lexico.c"

#define YYSTYPE ptno

ptno root = NULL, no;

int yylex();
void yyerror(char *);

%}

// Simbolo de partida
%start programa

// Simbolos terminais
%token T_PROGRAMA
%token T_INICIO
%token T_FIM
%token T_IDENTIF

%token T_LEIA
%token T_ESCREVA

%token T_SE
%token T_ENTAO
%token T_SENAO
%token T_FIMSE

%token T_ENQTO
%token T_FACA
%token T_FIMENQTO
%token T_MAIS
%token T_MENOS
%token T_VEZES
%token T_DIV
%token T_QUOTE

%token T_MAIOR
%token T_MENOR
%token T_IGUAL

%token T_E
%token T_OU
%token T_NAO

%token T_ATRIB
%token T_ABRE
%token T_FECHA

%token T_INTEIRO
%token T_LOGICO
%token T_V
%token T_F
%token T_NUMERO
%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV

%%

// Regras de produção
programa
	:
		{printf("");}
	cabecalho 
	variaveis
	T_INICIO lista_comandos
	T_FIM
		{
			printf(""); no = criaNo(programa, "programa"); adicionaFilho(no, $5);adicionaFilho(no, $3); adicionaFilho(no, $2); root = no;printf("digraph {\n node [shape=record, height=.1];\n");geradot(root,0);printf("}");		
		}
	;

cabecalho
	: T_PROGRAMA T_IDENTIF
		{
			ptno no=criaNo(identificador, atomo); $$ = no;
		}
	;

variaveis
	: /* vazio */ { $$ = NULL; }
	| declaracao_variaveis {$$ = $1;}
	;
	
declaracao_variaveis
	: declaracao_variaveis
	  tipo
		{CONTA_VARS = 0;}
	  lista_variaveis
	 	{
			printf(""); 
			ptno no = criaNo(declaracao_variaveis, "declaracao de variaveis"); adicionaFilho (no, $4); adicionaFilho (no, $2); adicionaFilho (no, $1); $$=no;
		}
	| tipo
		{CONTA_VARS = 0;}
	  lista_variaveis
	  	{
			printf(""); printf(""); 
			ptno no = criaNo(declaracao_variaveis,"declaracao de variaveis"); adicionaFilho (no, $3); adicionaFilho (no, $1); $$=no; 
		}
	;
	
tipo
	: T_LOGICO
		{
			ptno no = criaNo(tipo, "logico"); $$ = no;
		}
	| T_INTEIRO
		{
			ptno no = criaNo(tipo, "inteiro"); $$ = no;
		}
	;

lista_variaveis
	: lista_variaveis
	  T_IDENTIF
	  	{ 
	  		insere_variavel(atomo); 
	  		ptno no = criaNo(lista_de_variaveis, "lista variaveis");
        	adicionaFilho(no, criaNo(identificador, atomo));
		    adicionaFilho(no, $1);
	  		CONTA_VARS++; 
		    $$ = no; 
	  	}
	| T_IDENTIF
		{ 
			insere_variavel(atomo); ptno no = criaNo(lista_de_variaveis, " lista variaveis");
		    adicionaFilho(no, criaNo(identificador, atomo));

			CONTA_VARS++; 
		    $$ = no;

		}
	;
	
lista_comandos
	: /* vazio */ { $$ = NULL; }
	| comando lista_comandos
		{
			ptno no = criaNo(lista_de_comandos,"lista comandos"); adicionaFilho(no, $2); adicionaFilho(no, $1); $$ = no;
		}
	;
	
comando
	: entrada_saida 
	| repeticao 	
	| selecao  	
	| atribuicao 	
	;
	
entrada_saida
	: leitura	
	| escrita	
	;

leitura
	: T_LEIA
	  T_IDENTIF
	  	{
	  		POS_SIMB = busca_simbolo(atomo); if(POS_SIMB == -1)
	  			ERRO("Variavel [%s] nao declarada!", atomo); else{
	  			printf(""); 	printf(""); }
	  		
	  		no = criaNo(leitura,"leitura"); adicionaFilho(no,criaNo(identificador, atomo)); $$=no;
	  	}
	;

escrita
	: T_ESCREVA expressao
		{ 
			printf(""); 
			
	  		no = criaNo(escrita,"escrita"); adicionaFilho(no,$2); $$=no;
		}
	;
	
repeticao
	: T_ENQTO
		{
			printf(""); empilha(ROTULO);
		}
	expressao T_FACA
		{
			printf(""); empilha(ROTULO);
		}
	
	lista_comandos
	T_FIMENQTO
		{
			aux = desempilha(); printf(""); printf(""); ptno no = criaNo(repeticao, "repeticao");
		        adicionaFilho(no, $3);
		        if ($3) {
		            adicionaFilho(no, $6);
		        } else {
		            adicionaFilho(no, criaNo(lista_de_comandos, "listas comandos"));
		        }
		        $$ = no;
		}
	;
	
selecao
	: T_SE expressao
		{
			printf(""); empilha(ROTULO);
		}
		
	
	 T_ENTAO lista_comandos	T_SENAO
		{
			printf(""); printf(""); empilha(ROTULO);
		}
	
	lista_comandos
			T_FIMSE
		{
			printf(""); ptno no = criaNo(selecao, "selecao");
        		adicionaFilho(no, $2);
		        if ($5) {
		            adicionaFilho(no, $5);
		        } else {
		            adicionaFilho(no, criaNo(lista_de_comandos, "listas comandos"));
		        }
		        if ($8) {
		            adicionaFilho(no, $8);
		        } else {
		            adicionaFilho(no, criaNo(lista_de_comandos, "listas comandos"));
		        }
		        $$ = no;
		}
	;

atribuicao
	: 	T_IDENTIF
		{
			POS_SIMB = busca_simbolo(atomo); if(POS_SIMB == -1)
				ERRO("Variavel [%s] nao declarada!"); else
				empilha (TSIMB[POS_SIMB].desloca);
		}
	T_ATRIB	expressao
		{
			printf(""); ptno no = criaNo(atribuicao, "atribuicao"); adicionaFilho(no, $1); adicionaFilho(no, criaNo(identificador, atomo)); $$=no;
		}
	;

expressao
	: expressao T_VEZES expressao
		{
			printf(""); no = criaNo(multiplicacao, "multiplicacao");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	
		 	$$ = no;
		}
	| expressao T_DIV expressao
		{
			printf(""); no = criaNo(divisao, "divisao");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| expressao T_MAIS expressao
		{
			printf(""); no = criaNo(soma, "soma");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| expressao T_MENOS expressao
		{
			printf(""); no = criaNo(subtracao, "subtracao");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| expressao T_MAIOR expressao
		{
			printf(""); no = criaNo(maior, "maior");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| expressao T_MENOR expressao
		{
			printf(""); no = criaNo(menor, "menor");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| expressao T_IGUAL expressao
		{
			printf(""); no = criaNo(igual, "igual");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| expressao T_E expressao
		{
			printf(""); no = criaNo(conjuncao, "conjuncao");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| expressao T_OU expressao
		{
			printf(""); no = criaNo(disjuncao, "disjuncao");
		 	adicionaFilho(no, $3);
		 	adicionaFilho(no, $1);
		 	$$ = no;
		}
	| T_QUOTE
		{	char snum[sizeof(int)*8+1];
		 	itoa(CONTA_QUOTE, snum, 10);
			no = criaNo(texto, snum);
			CONTA_QUOTE++;
		 	$$ = no;
		}
	| termo	{$$=$1;}
	;

termo
	: 	T_IDENTIF 
		{
			POS_SIMB = busca_simbolo(atomo); if(POS_SIMB == -1)
				ERRO("Variavel [%s] nao declarada"); else{
				printf(""); }
			$$ = criaNo(variavel, atomo); 
		 	
		}
	| T_NUMERO 
		{
			printf(""); $$ = criaNo(numero, atomo);
		 	
		}
	| 	T_V
		{
			printf(""); $$ = criaNo(verdadeiro, "1");
		 	
		}
	| 	T_F
		{
			printf(""); $$ = criaNo(falso, "0");
		}
	| T_NAO termo
		{
			printf("");
        		ptno no = criaNo(nao, "nao");
        		adicionaFilho(no, $2);
       			$$ = no;
		}
	| T_ABRE expressao T_FECHA {$$=$2;}
	;


%%

yywrap(){
	return 1;
}

void yyerror (char *s){
	ERRO("ERRO SINTATICO");
}

int main(){
	return yyparse ();
}
