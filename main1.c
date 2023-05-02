/*Miguel Gewehr de Oliveira 2020100875*/
/*Aurea Santos de Oliveira 2021101303*/

#include "tDocumento.h"
#include "tTabelaDocumento.h"
#include "tTabelaPalavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

  if(argc != 3){
    printf("Precisa passar os argumentos!\n");
    exit(1);
  }
  clock_t start, end;
  start = clock();

  
  FILE *arq = fopen(argv[1], "r");

  char linha[4000];
  int numNews = 0, tamanho=0;
  char *aux = strtok(argv[1],".");  
  tamanho = strlen(aux);
  
  char diretorio[tamanho+2];
  strcpy(diretorio, aux);
  diretorio[tamanho] = '\0';


  tTabelaPalavra_pt tabelaPalavra = CriaTabelaPalavra();
  tTabelaDocumento_pt tabelaDocumento = CriaTabelaDoc();
  tDocumento_pt documento;

  if (arq == NULL) {
    printf("\nERRO NA ABERTURA DO ARQUIVO!\n");
    exit(1);
  }
  

  while (fgets(linha, 4000, arq) != NULL) {
    documento = CriaDocumento(linha, numNews);
    AbreDocumento(documento, diretorio);
    LeEPreenchePalavras(tabelaPalavra, documento);
    AddDocNaTabela(tabelaDocumento, documento);

    numNews++;
  }

  OrdenaTabela(tabelaPalavra);
  AddIndiceTabela(tabelaPalavra);

  AddTfidfTabelaPalavra(tabelaPalavra, numNews);
  
  AddPalavrasTabelaDoc(tabelaPalavra, tabelaDocumento);

  fclose(arq);
  
  CriaArqBinario(tabelaPalavra, argv[2]);
  CriaArqBinarioDoc(tabelaDocumento, argv[2]);

  int qtdWords = RetornaQtdPalavra(tabelaPalavra);
  int qtdDoc = RetornaQtdDoc(tabelaDocumento);

  printf("\nnumero de documentos: %d, numero de palavras: %d\n", qtdDoc,
         qtdWords);

  LiberaTabela(tabelaPalavra);
  LiberaTabelaDoc(tabelaDocumento);
  
  end = clock();
  printf("TEMPO :%lf\n", (double)(end-start)/CLOCKS_PER_SEC);

  return 0;
}