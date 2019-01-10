%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "tree.c"
#include "utilitarios.c"
#include "lexico.c"

#define YYSTYPE ptno

ptno root = NULL, pt;

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
	: cabecalho 
			{
				printf("\tINPP\n");

				pt = criaNo(programa, "programa");
				if($1) adicionaFilho(pt, $1);
			}
		variaveis
			{

			   if($2) adicionaFilho(pt, $2);
			} 
		T_INICIO 
		lista_comandos 
			{
				if($4) adicionaFilho(pt, $3);
			}
		T_FIM 
			{
				
				root = pt;
				mostra(root,0);			
				printf("\tFIMP\n");
			} 
	;

cabecalho
	: T_PROGRAMA T_IDENTIF
		{$$ = criaNo(10, atomo); }
	;

variaveis
	: /* vazio */
	| declaracao_variaveis
	;

declaracao_variaveis
	: declaracao_variaveis 
		tipo
			{CONTA_VARS = 0;} 
		lista_variaveis
			{printf ("\tAMEM\t%d\n", CONTA_VARS); } 

	| tipo
			{CONTA_VARS = 0;} 
	  lista_variaveis
	  		{printf ("\tAMEM\t%d\n", CONTA_VARS); } 
	;

tipo
	: T_LOGICO
	| T_INTEIRO
	;

lista_variaveis
	: lista_variaveis
	  T_IDENTIF
		{ insere_variavel (atomo); CONTA_VARS++;}
	| T_IDENTIF 
		{ insere_variavel (atomo); CONTA_VARS++;}
	;

lista_comandos
	: /* vazio */
	| comando lista_comandos
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
			POS_SIMB = busca_simbolo ( atomo ) ;
			if (POS_SIMB == -1)
				ERRO ( "Variavel [%s] nao declarada ! " , atomo ) ;
			else {
				printf ( "\tLEIA\n" ) ;
				printf ( "\tARZG\t%d\n" ,
					TSIMB[POS_SIMB ].desloca ) ;
		
			}
		}
	;
	
escrita
	: T_ESCREVA expressao {printf("\tESCR\n");}
	;

repeticao	
	: T_ENQTO{ printf("L%d\tNADA\n", ++ROTULO); empilha(ROTULO);}  expressao T_FACA { printf ("\tDSFV\tL%d\n", ++ROTULO); empilha(ROTULO); } lista_comandos T_FIMENQTO {aux = desempilha(); printf("\tDSVS\tL%d\n", desempilha()); printf("L%d\tNADA\n", aux); }
	;

selecao
	: T_SE expressao { printf("\tDSVF\tL%d\n", ++ROTULO); empilha(ROTULO);} T_ENTAO lista_comandos T_SENAO { printf  ("\tDSVS\tL%d\n", ++ROTULO); printf("L%d\tNADA\n", desempilha()); empilha(ROTULO); } lista_comandos T_FIMSE { printf("L%d\tNADA\n", desempilha()); }
	;

atribuicao
	: T_IDENTIF T_ATRIB expressao 
	;

expressao
	: expressao T_VEZES expressao { printf("\tMULT\n"); }
	| expressao T_DIV expressao { printf("\tDIVI\n"); }
	| expressao T_MAIS expressao { printf("\tSOMA\n"); }
	| expressao T_MENOS expressao { printf("\tSUBT\n"); }
	| expressao T_MAIOR expressao { printf("\tCMMA\n"); }
	| expressao T_MENOR expressao { printf("\tCMME\n"); }
	| expressao T_IGUAL expressao { printf("\tCMIG\n"); }
	| expressao T_E expressao { printf("\tCONJ\n"); } 
	| expressao T_OU expressao { printf("\tDISJ\n"); }
	| termo
	;

termo
	: T_IDENTIF 
			{
			POS_SIMB = busca_simbolo ( atomo ) ;
			if (POS_SIMB == -1)
				ERRO ( "Va r i ave l [%s ] nao de c larada ! " ,
			atomo ) ;
			else {
				printf ( "\tLEIA\n" ) ;
				printf ( "\tARZG\t%d\n" ,
					TSIMB[POS_SIMB ].desloca ) ;
		
			}
		}
	| T_NUMERO 
		{ printf ( "\tCRCT \t%s \n" , atomo ) ; }
	| T_V 
		{ printf ( "\tCRCT\t 1 \n") ; }
	| T_F 
		{ printf ( "\tCRCT \t 0 \n" , atomo ) ; }
	| T_NAO termo 
		{ printf ( "\tNEGA \t%s \n") ; }
	| T_ABRE expressao T_FECHA
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
