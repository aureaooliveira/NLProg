all: main1.c main2.c libalbum.a
	gcc -g -Wall -o main1 main1.c -L . -lalbum -I headers/ -lm
	gcc -g -Wall -o main2 main2.c -L . -lalbum -I headers/ -lm  

arq_objetos/tDocumento.o: TADS/tDocumento.c headers/tDocumento.h
	gcc -g -Wall -I headers/ -o arq_objetos/tDocumento.o TADS/tDocumento.c -c 

arq_objetos/tPalavra.o: TADS/tPalavra.c headers/tPalavra.h
	gcc -g -Wall -I headers/ -o arq_objetos/tPalavra.o TADS/tPalavra.c -c

arq_objetos/tPropriedade.o: TADS/tPropriedade.c headers/tPropriedade.h
	gcc -g -Wall -I headers/ -o arq_objetos/tPropriedade.o TADS/tPropriedade.c -c

arq_objetos/tTabelaDocumento.o: TADS/tTabelaDocumento.c headers/tTabelaDocumento.h
	gcc -g -Wall -I headers/ -o arq_objetos/tTabelaDocumento.o TADS/tTabelaDocumento.c -c
	
arq_objetos/tTabelaPalavra.o: TADS/tTabelaPalavra.c headers/tTabelaPalavra.h
	gcc -g -Wall -I headers/ -o arq_objetos/tTabelaPalavra.o TADS/tTabelaPalavra.c -c
	
arq_objetos/util.o: TADS/util.c headers/util.h
	gcc -g -Wall -I headers/ -o arq_objetos/util.o TADS/util.c -c

libalbum.a: arq_objetos/tDocumento.o arq_objetos/tPalavra.o arq_objetos/tPropriedade.o arq_objetos/tTabelaDocumento.o arq_objetos/tTabelaPalavra.o arq_objetos/util.o
	ar -crs libalbum.a arq_objetos/tDocumento.o arq_objetos/tPalavra.o arq_objetos/tPropriedade.o arq_objetos/tTabelaDocumento.o arq_objetos/tTabelaPalavra.o arq_objetos/util.o



clean:
	rm -f main1 main2 *.exe arq_objetos/*.o  *.a