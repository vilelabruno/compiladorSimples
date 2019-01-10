simples : ;\
	flex -t lexico.l > lexico.c;\
	bison -v -d sintatico.y -o sintatico.c;\
	gcc sintatico.c -o simples
cmptao : ;\
	flex -t lexico.l > lexico.c;\
	bison -v -d sintatico.y -o sintatico.c;\
	gcc sintatico.c -o simples
	./simples < test3.simples > d.dot
	dot -Tsvg d.dot -o d.svg


limpa   : ;\
	rm -f lexico.c sintatico.c sintatico.output *~ sintatico.h simples\
