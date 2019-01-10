#include "string.h"

#define YYSTYPE ptno

typedef struct no *ptno; //renomeando "struct no *" para ptno

struct no {
	int tipo;
	char *valor;
	ptno filho, irmao;
};

ptno criaNo (int, char *);
void adicionaFilho (ptno, ptno);
void mostra (ptno, int);