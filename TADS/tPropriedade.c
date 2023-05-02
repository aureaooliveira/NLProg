#include "tPropriedade.h"

struct tPropriedade {
  int documento;//Quando se trata da propriedade de um documento representa uma palavra;
  int frequencia;
  float tfidf;
};

void AddFrequenciaPalavra(tDocumento_pt doc, tPalavra_pt palavra,
                          tPalavra_pt palavraAtual) {

  int igual = 0;
  int qtdInfo = RetornaQtdInfosPalavra(palavra);
  tPropriedade_pt *prop = RetornaPropiedadePalavra(palavra);
  
  for (int i = 0; i < qtdInfo; i++) {
    if (prop[i]->documento == RetornaIndiceDoc(doc)) {
      prop[i]->frequencia++;
      LiberaPropWordRepetida(RetornaPropiedadePalavra(palavraAtual));

      igual = 1;
    }
  }

  if (igual == 0) {
    if (qtdInfo >= RetornaMaxInfosPalavra(palavra)) {
      RealocaPalavra(palavra);
    }
    prop[qtdInfo] = RetornaPropiedadePalavra(palavraAtual)[0];
    AddQtdInfoPalavra(palavra);
  }
}

tPropriedade_pt *AlocaPropPalavra() {
  tPropriedade_pt *p =
      (tPropriedade_pt *)malloc(sizeof(tPropriedade_pt) * 16000);
  return p;
}

tPropriedade_pt *AlocaPropDocumento() {
  tPropriedade_pt *p =
      (tPropriedade_pt *)malloc(sizeof(tPropriedade_pt) * 5000);

  return p;
}

tPropriedade_pt InicializaPropPalavra(tDocumento_pt doc) {
  tPropriedade_pt p = (tPropriedade_pt)malloc(sizeof(tPropriedade));
  p->documento = RetornaIndiceDoc(doc);
  p->frequencia = 1;
  p->tfidf = 0.0;
  return p;
}

void ImprimePropPalavra(tPropriedade_pt p) {
  printf("doc:%d\n", p->documento);
  printf("frequencia:%d\n", p->frequencia);
  printf("TF-IDF:%f\n", p->tfidf);
}

void ImprimePropDoc(tPropriedade_pt p) {
  printf("palavra: %d\n", p->documento);
  printf("frequencia:%d\n", p->frequencia);
  printf("TF-IDF:%f\n", p->tfidf);
}

void CalculaTfidf(tPropriedade_pt propriedade, int numDocs, int docAparece) {

  float tfidf = 0.0;

  tfidf =
      propriedade->frequencia * ((log((1 + numDocs) / (1 + docAparece))) + 1);

  propriedade->tfidf = tfidf;
}

void addPalavraInfoDoc(tDocumento_pt doc, int palavra, int freq, float tfidf) {

  int qtdInfoDoc = RetornaQtdInfoDoc(doc);
  tPropriedade_pt *propDoc = RetornaPropriedadeDoc(doc);
  
  if (qtdInfoDoc >= RetornaMaxInfoDoc(doc)) {
    RealocaInfoDocumento(doc);
  }
  
  propDoc[qtdInfoDoc] = InicializaPropDoc(palavra, freq, tfidf);

  AddQtdInfoDoc(doc);
}

void AddPalavraFreq(tPropriedade_pt p, int palavra, int frequencia) {
  p->documento = palavra;
  p->frequencia = frequencia;
}

tPropriedade_pt InicializaPropDoc(int palavra, int frequencia, float tfidf) {
  tPropriedade_pt p = (tPropriedade_pt)malloc(sizeof(tPropriedade));
  p->documento = palavra;
  p->frequencia = frequencia;
  p->tfidf = tfidf;
  return p;
}

tPropriedade_pt *RealocaVetorPropriedade(tPropriedade_pt *p, int novoMax) {

  p = (tPropriedade_pt *)realloc(p, sizeof(tPropriedade_pt) * novoMax);

  return p;
}

void LiberaPropriedades(tPropriedade_pt *propriedade, int qtd) {
  if (propriedade != NULL) {
    for (int i = 0; i < qtd; i++) {
      if (propriedade[i] != NULL) {
        free(propriedade[i]);
        propriedade[i] = NULL;
      }
    }
    free(propriedade);
  }

  propriedade = NULL;
}

void LiberaPropWordRepetida(tPropriedade_pt *propriedade) {
  if (propriedade != NULL) {
    if (propriedade[0] != NULL) {
      free(propriedade[0]);
      propriedade[0] = NULL;
    }
  }
}

int RetornaDocPropriedade(tPropriedade_pt p) { return p->documento; }

int RetornaFrequencia(tPropriedade_pt propriedade) {
  return propriedade->frequencia;
}

float RetornaIfidf(tPropriedade_pt propriedade) { return propriedade->tfidf; }

/*********** Funcoes especificas do programa dois *****************/

tPropriedade_pt *AlocaPropriedadeLeitura(int qtdInfo) {

  tPropriedade_pt *p =
      (tPropriedade_pt *)malloc(sizeof(tPropriedade_pt) * (qtdInfo));

  return p;
}

tPropriedade_pt AddPropriedadesLeitura(int documento, int frequencia,
                                       float tfidf) {

  tPropriedade_pt propriedade = (tPropriedade_pt)malloc(sizeof(tPropriedade));

  propriedade->documento = documento;
  propriedade->frequencia = frequencia;
  propriedade->tfidf = tfidf;

  return propriedade;
}

int ComparaFrequeciasVetorInfos(const void *p1, const void *p2) {

  tPropriedade_pt *pp1 = (tPropriedade_pt *)p1;
  tPropriedade_pt *pp2 = (tPropriedade_pt *)p2;

  return RetornaFrequencia(*pp2) - RetornaFrequencia(*pp1);
}

void FrequenciaPorClasse(tPropriedade_pt *p, int tamanho,
                         tTabelaDocumento_pt tab) {

  tPropriedade_pt vetor =
      (tPropriedade_pt)malloc(sizeof(tPropriedade) * tamanho);

  int qtdVetor = 0;
  char tipo[4];
  char tipoTab[4];

  for (int i = 0; i < tamanho; i++) {

    //printf("%s\n", RetornaTipoDoc(RetornaDocNaPosicaoX(tab, p[i]->documento)));

    if (qtdVetor == 0) {
      vetor[i].documento = p[i]->documento;
      vetor[i].frequencia = p[i]->frequencia;
      qtdVetor = 1;

    } else {

      int igual = 0;
      for (int a = 0; a < qtdVetor; a++) {

        strcpy(tipoTab, RetornaTipoDoc(RetornaDocNaPosicaoX(tab, p[i]->documento)));
        strcpy(tipo, RetornaTipoDoc(RetornaDocNaPosicaoX(tab, vetor[a].documento)));
        
        if (strcmp(tipoTab, tipo)==0) {
          vetor[a].frequencia += p[i]->frequencia;
          igual = 1;
        }
      }

      if (igual == 0) {
        vetor[qtdVetor].documento = p[i]->documento;
        vetor[qtdVetor].frequencia = p[i]->frequencia;
        qtdVetor++;
      }
    }
  }

  printf("\nfrequencia da palavra por classes:\n\n");
  for (int a = 0; a < qtdVetor; a++) {

    printf("classe: %s ",
           RetornaTipoDoc(RetornaDocNaPosicaoX(tab, vetor[a].documento)));
    printf("frequencia: %d\n", vetor[a].frequencia);
  }
  
  free(vetor);
}

 void IncrementaFrequencia(tPropriedade_pt p){
   p->frequencia++;
 }

void AlocaPropriedade_pt(tPropriedade_pt* p,int numTotal){

  for(int i=0;i<numTotal;i++){
    p[i] = (tPropriedade_pt)malloc(sizeof(tPropriedade));
  }
}

float CalculaCosseno(tPropriedade_pt* texto ,int qtdVetorP,tDocumento_pt doc){

  int vetorComum[qtdVetorP];
  int qtdComum=0;

  for(int i=0;i<qtdVetorP;i++){

      for(int j=0;j<RetornaQtdInfoDoc(doc);j++){

          int palavra = RetornaDocPropriedade(texto[i]);
          int palavraDoc = RetornaDocPropriedade(RetornaPropriedadeDoc(doc)[j]);

        if(palavra == palavraDoc){
          
          vetorComum[qtdComum] = RetornaDocPropriedade(texto[i]);
          qtdComum++;
          
        }
      }

  }

  //--------------------ate aqui ok-----------------
  

  double vetorTexto[qtdComum];
  double vetorDoc[qtdComum];

  for(int i=0;i<qtdComum;i++){
    for(int j=0;j<qtdVetorP;j++){

      if(vetorComum[i]==
    RetornaDocPropriedade(texto[j]) ){
      vetorTexto[i] = RetornaIfidf(texto[j]);
    }
    }
    
  }

  for(int i=0;i<qtdComum;i++){
    int palavra = vetorComum[i];
    for(int j=0;j<RetornaQtdInfoDoc(doc);j++){
      int palavraDoc = RetornaDocPropriedade(RetornaPropriedadeDoc(doc)[j]);
      if(palavra==palavraDoc){
        vetorDoc[i] = RetornaIfidf(RetornaPropriedadeDoc(doc)[j]);
      }
    }
  }

  double normaTexto = 0.0;
  double normaDoc = 0.0;
  double prodInterno=0.0;
  for(int i=0;i<qtdComum;i++){
    prodInterno += vetorTexto[i] * vetorDoc[i];
   

  }


  normaTexto = CalculaNormaVetor(texto,qtdVetorP);
  normaDoc = CalculaNormaVetor(RetornaPropriedadeDoc(doc),RetornaQtdInfoDoc(doc));

  double cosseno = prodInterno / (normaDoc * normaTexto) ;


  return cosseno;



}

 double CalculaNormaVetor(tPropriedade_pt* prop,int num){
double soma=0.0;
double norma= 0.0;




  for(int i=0;i<num;i++){

    soma = soma+ pow(prop[i]->tfidf,2);

  }

  norma = sqrt(soma);

  return norma;


}




int CalculaFreqTotalProp(tPropriedade_pt *propriedade, int qtdInfo){

  int totalFreq =0;

  for(int i=0; i < qtdInfo; i++)
    totalFreq += propriedade[i]->frequencia;

  return totalFreq;
}

int OrdenaCossenos(const void *cos1,const void *cos2){

  tPropriedade_pt cos11 = *(tPropriedade_pt*)cos1;
  tPropriedade_pt cos22 = *(tPropriedade_pt*)cos2;
 
  return RetornaIfidf(cos22) - RetornaIfidf(cos11);
}

void select_sort (tPropriedade_pt *a, int qtd) {
    int menor;
    for (int i=0; i<qtd; i++) {
        menor = i;
        for (int j=i+1; j<qtd; j++) {
            if ((a[j]->tfidf < a[menor]->tfidf)) {
                menor = j;
            }
        }
        int indice = a[i]->documento;
        float aux = a[i]->tfidf;
        a[i]->tfidf = a[menor]->tfidf;
        a[i]->documento = a[menor]->documento;
        a[menor]->tfidf = aux;
        a[menor]->documento = indice;
    }
}

