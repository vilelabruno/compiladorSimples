#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TOTALINST 21
char *inst[TOTALINST]={
	"CRVG",
	"CRCT",
	"SOMA",
	"SUBT",
	"MULT",
	"DIVI",
	"CMIG",
	"CMMA",
	"CMME",
	"CONJ",
	"DISJ",
	"NEGA",
	"ARZG",
	"DSVS",
	"DSVF",
	"NADA",
	"ESCR",
	"LEIA",
	"INPP",
	"AMEM",
	"FIMP"
};

enum codinst{CRVG,CRCT,SOMA,SUBT,MULT,DIVI,CMIG,CMMA, CMME, CONJ,DISJ,NEGA,ARZG,DSVS,DSVF,NADA,ESCR,LEIA,INPP,AMEM,FIMP};

struct prog { int r,i,o;}
	P[500];
int 
	L[50];
int 
	M[500];

int busca_instrucao(char *s);
int carrega_programa(char *s,int *nro);
void mostra_programa(int nro);
void executa_programa(void);

main(int argc, char *argv[]){
	int i,nroinst;
	argc--;
	argv++;
	if(argc <1){
		puts("\nMVS_-_Maquina_Virtual_Simples");
		puts("USO:_mvs_<nomedoarquivo.mvs>\n\n");
		exit(0);
	}
	if(carrega_programa(argv[0],&nroinst)){
		mostra_programa(nroinst);
		executa_programa();
		printf("Fim_do_programa.\n");
	}
	return 1;
}

int busca_instrucao(char *s){
	int i;
	for(i=TOTALINST-1;i>=0 && strcmp(inst[i],s);i--);
	return i;
}

int carrega_programa(char *s, int *nro){
	FILE *arq;
	char linha[100],*p,str[6];
	int j;
	if((arq = fopen(s,"r")) == NULL){
		puts("\n\nErro_na_abertura_do_arquivo\n\n");
		return 0;
	}
	*nro = 0;
	while(!feof(arq)){
		fgets(linha,100,arq);
		linha [strlen(linha)-1]='\0';
		if(linha[0] == 'L'){
			p = (char *)strtok(linha,"\t");
			p++;
			P[*nro].r = atoi(p);
			P[*nro].i = busca_instrucao("NADA");
			P[*nro].o = -1;
			L[P[*nro].r]=*nro;
		}else{
			p = (char *)strtok(linha,"\t");
			P[*nro].r = -1;
			P[*nro].i = busca_instrucao(p);
			p = (char *)strtok(NULL,"\t");
			if(!p)
				P[*nro].o=-1;
			else{
				if(*p == 'L') p++;
				P[*nro].o = atoi(p);
			}
			if(P[*nro].i == TOTALINST -1){
				(*nro)++;
				break;
			}
		}
	}
	fclose(arq);
	return 1;
}

void mostra_programa(int nro){
	int i;
	for(i=0;i<nro;i++){
		printf("%d\t%s\t%d\n",P[i].r,inst[P[i].i],P[i].o);
	}
}

void executa_programa (void)
{
	int i = 0, s;
	char numstr [6];
	while (1) {
		switch (P[i].i) {
			case CRCT : s++; M[s] = P[i].o; i++;
				    break;
			case CRVG : s++; M[s] = M[P[i].o]; i++;
				    break;
			case ARZG : M[P[i].o] = M[s]; s--; i++;
				    break;
			case SOMA : M[s-1] = M[s-1] + M[s]; s--; i++;
				    break;
			case SUBT : M[s-1] = M[s-1] - M[s]; s--; i++;
				    break;
			case MULT : M[s-1] = M[s-1] * M[s]; s--; i++;
				    break;
			case DIVI : M[s-1] = M[s-1] / M[s]; s--; i++;
				    break;
			case CONJ : if (M[s-1] && M[s]) M[s-1] = 1;
				    else M[s-1] = 0;
				    s--; i++;
				    break;
			case DISJ : if (M[s-1] || M[s]) M[s-1] = 1;
				    else M[s-1] = 0;
				    s--; i++;
				    break;
			case NEGA : M[s] = 1 - M[s]; i++;
				    break;
			case CMME : if (M[s-1] < M[s]) M[s-1] = 1;
				    else M[s-1] = 0;
				    s--; i++;
				    break;
			case CMMA : if (M[s-1] > M[s]) M[s-1] = 1;
				    else M[s-1] = 0;
				    s--; i++;
				    break;
			case CMIG : if (M[s-1] == M[s]) M[s-1] = 1;
				    else M[s-1] = 0;
				    s--; i++;
				    break;
			case DSVS : i = L[P[i].o];
				    break;
			case DSVF : if (M[s] == 0) i = L[P[i].o];
				    else i++; s--;
				    break;
			case NADA : i++;
				    break;
			case FIMP : printf("\n\n"); return;
			case LEIA : s++; printf("?_");
				    fgets (numstr, 5, stdin);
				    M[s] = atoi (numstr); i++;
				    break;
			case ESCR : printf("\nSAIDA_=_%d",M[s]);s--;i++;
					break;
			case AMEM : s=s+P[i].o;i++;
					break;
			case INPP : s = -1;i++;
					break;
			default : puts("Instrucao_MVS_desconhecida!");
					exit(0);
		}
	}
}





















