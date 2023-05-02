/*Miguel Gewehr de Oliveira 2020100875*/
/*Aurea Santos de Oliveira 2021101303*/

#include "tTabelaPalavra.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if(argc!=3){
      printf("erro na passagem de argumentos\n");
      exit(1);
  }

  tTabelaPalavra_pt tabela;
  tTabelaDocumento_pt tabelaDoc;
  char *nome = (char *)malloc(sizeof(char) * 100);

  FILE *arq = fopen(argv[1], "rb");
  if(arq==NULL){
    printf("nao foi possivel abrir o arquivo.\n");
    exit(1);
  }

  tabela = LeituraArqBinP(arq, nome);

  tabelaDoc = LeituraArqBinD(arq, nome);
  AddFreqTotalTabela(tabelaDoc);

  fclose(arq);

  //ImprimeTabelaDoc(tabelaDoc);
  //ImprimeTabelaPalavra(tabela);

  int qtdDoc = RetornaQtdDoc(tabelaDoc);
  
  int opcao = 0;

  printf("--------------------------------------------------\n");
  printf("Escolha uma opcao do menu:\n");
  printf("Buscar Noticia: 1\n");
  printf("Classificar noticia: 2\n");
  printf("Relatorio da palavra: 3\n");
  printf("Relatorio do documentos: 4\n");
  printf("Digite qualquer outra tecla para sair do programa!\n");
  printf("---------------------------------------------------\n");

  while (scanf("%d", &opcao)) {
    getchar();

    switch (opcao) {

    case 1:
      BuscarPalavras(tabela, qtdDoc);
      break;

    case 2:
      ClassificarNoticia(tabelaDoc, atoi(argv[2]), tabela);
      break;

    case 3:
      RelatorioPalavra(tabela, tabelaDoc);
      break;

    case 4:
      RelatorioDoc(tabelaDoc);
      break;

    default:
      printf("Nao é uma opcao\n");
      break;
    }

    printf("\n-------------------------------------------------\n");
    printf("Escolha uma opcao do menu:\n");
    printf("Buscar Noticia: 1\n");
    printf("Classificar noticia: 2\n");
    printf("Relatorio da palavra: 3\n");
    printf("Relatorio do documentos: 4\n");
    printf("Digite qualquer outra tecla para sair do programa!\n");
    printf("-------------------------------------------------\n\n");
  }

  free(nome);
  LiberaTabela(tabela);
  LiberaTabelaDoc(tabelaDoc);

  return 0;
}