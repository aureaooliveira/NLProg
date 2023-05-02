#include "tDocumento.h"

struct tDocumento {
  char *nome;
  char *tipo;
  int indice;
  tPropriedade_pt *infos;
  int freqTotal;
  int maxInfo;
  int qtdInfo;
  FILE *arquivo;
};

tDocumento_pt AlocaDocumento() {

  tDocumento_pt documento = (tDocumento_pt)malloc(sizeof(tDocumento));

  return documento;
}

tDocumento_pt CriaDocumento(char *link, int indice) {

  tDocumento_pt documento = AlocaDocumento();
  char *aux = strtok(link, " ");
  documento->nome = (char *)malloc(sizeof(char) * strlen(aux) + 1);
  strcpy(documento->nome, aux);
  
  aux = strtok(NULL, "\n");
  documento->tipo = (char *)malloc(sizeof(char) * strlen(aux) + 1);
  strcpy(documento->tipo, aux);

  documento->indice = indice;
  documento->qtdInfo = 0;
  documento->infos = AlocaPropDocumento();
  documento->freqTotal = 0;

  documento->maxInfo = 5000;

  return documento;
}

void AbreDocumento(tDocumento_pt documento, char *diretorio) {

  char nomeArquivo[200];
  char *aux = strchr(documento->nome , '/');
 
  strcpy(nomeArquivo, diretorio);
  strcat(nomeArquivo, aux);
  documento->arquivo = fopen(nomeArquivo, "r");
  if (documento->arquivo == NULL) {
    printf("ERRO NA ABERTURA DO ARQUIVOaaaa!\n");
    exit(1);
  }
}

void AddQtdInfoDoc(tDocumento_pt doc) { doc->qtdInfo++; }

void ImprimeDoc(tDocumento_pt doc) {

  printf("%d ", doc->indice);
  printf("%s\n", doc->nome);

  for (int i = 0; i < doc->qtdInfo; i++) {
    ImprimePropDoc(doc->infos[i]);
  }
  printf("-------\n");
}

void RealocaInfoDocumento(tDocumento_pt doc) {
  doc->maxInfo = doc->maxInfo * 2;
  RealocaVetorPropriedade(doc->infos, doc->maxInfo);
}

void LiberaDocumento(tDocumento_pt documento) {

  LiberaPropriedades(documento->infos, documento->qtdInfo);

  if (documento->tipo != NULL) {
    free(documento->tipo);
    documento->tipo = NULL;
  }

  if (documento->nome != NULL) {
    free(documento->nome);
    documento->nome = NULL;
  }
  if (documento != NULL) {
    free(documento);
    documento = NULL;
  }
}

FILE *RetornaArquivoDoc(tDocumento_pt doc) { return doc->arquivo; }

char *RetornaNomeDoc(tDocumento_pt doc) { return doc->nome; }

int RetornaIndiceDoc(tDocumento_pt doc) { return doc->indice; }

tPropriedade_pt *RetornaPropriedadeDoc(tDocumento_pt doc) { return doc->infos; }

int RetornaQtdInfoDoc(tDocumento_pt doc) { return doc->qtdInfo; }

int RetornaMaxInfoDoc(tDocumento_pt doc) { return doc->maxInfo; }

char *RetornaTipoDoc(tDocumento_pt documento){
  return documento->tipo;
}



/*********** Funcoes especificas do programa dois *****************/

tDocumento_pt CriaDocLeitura(int indice){

  tDocumento_pt doc = AlocaDocumento();
  doc->nome = (char*) malloc(sizeof(char)*50);
  doc->tipo = (char*) malloc(sizeof(char)*4);
  doc->arquivo = NULL;

  doc->indice = indice;
  doc->maxInfo = 10000;
  doc->qtdInfo = 0;
  doc->freqTotal = 0;

  return doc;
}

void AddQtdInfoDocLeitura(tDocumento_pt doc, int qtdInfo){
  doc->qtdInfo = qtdInfo;
  doc->infos = (tPropriedade_pt*) malloc(sizeof(tPropriedade_pt)*qtdInfo);
}

void AddPropDocLeitura(tDocumento_pt documento, int palavra, int frequencia, float tfidf, int indice){
  documento->infos[indice] = AddPropriedadesLeitura(palavra, frequencia, tfidf);
}

void CalculaFreqTotal(tDocumento_pt doc){
  doc->freqTotal = CalculaFreqTotalProp(doc->infos, doc->qtdInfo);
}

int RetornaFreqTotal(tDocumento_pt doc){
  return doc->freqTotal;
}

