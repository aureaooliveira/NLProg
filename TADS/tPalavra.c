#include "tPalavra.h"

struct tPalavra {
  int indice;
  char *nome;
  tPropriedade_pt *infos;
  int maxInfos;
  int qtdIfos;
};

tPalavra_pt AlocaPalavra() {

  tPalavra_pt palavra = (tPalavra_pt)malloc(sizeof(tPalavra));
  palavra->nome = (char *)malloc(sizeof(char) * 50);
  return palavra;
}

tPalavra_pt CriaPalavra(char *nome, tDocumento_pt doc) {

  tPalavra_pt palavra = AlocaPalavra();
  palavra->infos = AlocaPropPalavra();

  strcpy(palavra->nome, nome);

  palavra->infos[0] = InicializaPropPalavra(doc);
  palavra->maxInfos = 16000;
  palavra->qtdIfos = 1;

  return palavra;
}

void LeEPreenchePalavras(tTabelaPalavra_pt tabela,tDocumento_pt documento) {

  int igual = 0;
  tPalavra_pt palavra;
  char nome[50];
  FILE *arq = RetornaArquivoDoc(documento);

  while (!feof(arq)) {
    fscanf(arq, "%s", nome);

    palavra = CriaPalavra(nome, documento);
    
    igual = AddPalavraNaTabela(palavra, tabela, documento);
    if (igual == 1)
      LiberaPalavraRepetida(palavra);
  }
  
  fclose(arq);
}

void ImprimePalavra(tPalavra_pt palavra) {

  printf("-------palavra: %s %d-------------\n", palavra->nome,
         palavra->indice);

  for (int i = 0; i < palavra->qtdIfos; i++) {
    ImprimePropPalavra(palavra->infos[i]);
  }
}

void AddIndice(tPalavra_pt palavra, int indice) { 
  palavra->indice = indice; 
  }

void AddQtdInfoPalavra(tPalavra_pt p) { p->qtdIfos++; }

void RealocaPalavra(tPalavra_pt p) {

  p->maxInfos = p->maxInfos * 2; 
 p->infos = RealocaVetorPropriedade(p->infos, p->maxInfos);
}

void LiberaPalavra(tPalavra_pt p) {

  if (p != NULL) {
    if (p->nome != NULL) {
      free(p->nome);
      p->nome = NULL;
    }
    LiberaPropriedades(p->infos, p->qtdIfos);
    free(p);
  }

  p = NULL;
}

void LiberaPalavraRepetida(tPalavra_pt p) {

  if (p != NULL) {
    if (p->nome != NULL) {
      free(p->nome);
      p->nome = NULL;
      free(p->infos);
      p->infos = NULL;
    }
    free(p);
    p = NULL;
  }
}

int RetornaQtdInfosPalavra(tPalavra_pt p) { return p->qtdIfos; }

int RetornaIndicePalavra(tPalavra_pt p) { return p->indice; }

char *RetornaNomePalavra(tPalavra_pt palavra) { return palavra->nome; }

tPropriedade_pt *RetornaPropiedadePalavra(tPalavra_pt p) { return p->infos; }


int RetornaMaxInfosPalavra(tPalavra_pt p){
  return p->maxInfos;
}
/*********** Funcoes especificas do programa dois *****************/

void AddNomePalavraLeitura(tPalavra_pt palavra, char* nome){
  strcpy(palavra->nome, nome);
}

tPalavra_pt CriaPalavraLeitura(){

  tPalavra_pt palavra = AlocaPalavra();
  palavra->maxInfos=10;

  return palavra;
}

void AddQtdInfoPalavraLeitura(tPalavra_pt palavra, int qtdInfo){
  palavra->qtdIfos = qtdInfo;
  palavra->infos = AlocaPropriedadeLeitura(qtdInfo);
}

void AddPropriedadesPalavraLeitura(tPalavra_pt palavra, int indice, int documento, int frequencia, float tfidf){
  palavra->infos[indice] = AddPropriedadesLeitura(documento, frequencia, tfidf);
}