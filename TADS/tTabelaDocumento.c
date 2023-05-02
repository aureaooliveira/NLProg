#include "tTabelaDocumento.h"

struct tTabelaDocumento {
  int qtd;
  int max;
  tDocumento_pt *documentos;
};

tTabelaDocumento_pt CriaTabelaDoc() {
  tTabelaDocumento_pt tabela =
      (tTabelaDocumento_pt)malloc(sizeof(tTabelaDocumento));

  tabela->documentos = (tDocumento_pt *)malloc(sizeof(tDocumento_pt) * 200);
  tabela->qtd = 0;
  tabela->max = 200;
  return tabela;
}
int x = 0;

void AddPalavrasTabelaDoc(tTabelaPalavra_pt tabPalavra,
                          tTabelaDocumento_pt tabDoc) {

  int qtdInfoWord = 0, docWord = 0, freqWord = 0;
  float tfidfWord = 0.0;

  for (int i = 0; i < tabDoc->qtd; i++) {

    for (int a = 0; a < RetornaQtdPalavra(tabPalavra); a++) {
      qtdInfoWord =
          RetornaQtdInfosPalavra(RetornaPalavraPosicaoX(tabPalavra, a));
      for (int b = 0; b < qtdInfoWord; b++) {
        docWord = RetornaDocPropriedade(
            RetornaPropiedadePalavra(RetornaPalavraPosicaoX(tabPalavra, a))[b]);

        if (docWord == RetornaIndiceDoc(tabDoc->documentos[i])) {
          freqWord = RetornaFrequencia(RetornaPropiedadePalavra(
              RetornaPalavraPosicaoX(tabPalavra, a))[b]);

          tfidfWord = RetornaIfidf(RetornaPropiedadePalavra(
              RetornaPalavraPosicaoX(tabPalavra, a))[b]);

          addPalavraInfoDoc(tabDoc->documentos[i], a, freqWord, tfidfWord);
        }
      }
    }
  }
}

void AddDocNaTabela(tTabelaDocumento_pt tabDoc, tDocumento_pt doc) {
  if (tabDoc->qtd >= tabDoc->max) {
    RealocaTabelaDoc(tabDoc);
  }
  tabDoc->documentos[RetornaIndiceDoc(doc)] = doc;
  tabDoc->qtd++;
}

void RealocaTabelaDoc(tTabelaDocumento_pt tab) {

  tab->max = tab->max * 2;

  tab->documentos = (tDocumento_pt *)realloc(tab->documentos,
                                             sizeof(tDocumento_pt) * tab->max);
}

void CriaArqBinarioDoc(tTabelaDocumento_pt tabela, char *nomeArq) {

  int tamanho = 0, qtdInfo = 0, documento = 0, frequencia = 0;
  float tfidf = 0.0;
  char nome[100];
  char tipo[4];

  FILE *arq = fopen(nomeArq, "ab");

  fwrite(&tabela->qtd, sizeof(int), 1, arq);

  for (int i = 0; i < tabela->qtd; i++) {
    tamanho = strlen(RetornaNomeDoc(tabela->documentos[i]));
    fwrite(&tamanho, sizeof(int), 1, arq);

    strcpy(nome, RetornaNomeDoc(tabela->documentos[i]));
    fwrite(nome, sizeof(char) * tamanho, 1, arq);

    strcpy(tipo, RetornaTipoDoc(tabela->documentos[i]));
    fwrite(tipo, sizeof(char) * 4, 1, arq);

    qtdInfo = RetornaQtdInfoDoc(tabela->documentos[i]);
    fwrite(&qtdInfo, sizeof(int), 1, arq);

    for (int j = 0; j < qtdInfo; j++) {
      documento = RetornaDocPropriedade(
          RetornaPropriedadeDoc(tabela->documentos[i])[j]);
      fwrite(&documento, sizeof(int), 1, arq);

      frequencia =
          RetornaFrequencia(RetornaPropriedadeDoc(tabela->documentos[i])[j]);
      fwrite(&frequencia, sizeof(int), 1, arq);

      tfidf = RetornaIfidf(RetornaPropriedadeDoc(tabela->documentos[i])[j]);
      fwrite(&tfidf, sizeof(float), 1, arq);
    }
  }
  fclose(arq);
}

void LiberaTabelaDoc(tTabelaDocumento_pt tabela) {

  for (int i = 0; i < tabela->qtd; i++) {
    LiberaDocumento(tabela->documentos[i]);
  }
  free(tabela->documentos);
  free(tabela);
}

int RetornaQtdDoc(tTabelaDocumento_pt tabela) { return tabela->qtd; }

void ImprimeTabelaDoc(tTabelaDocumento_pt tabDoc) {

  for (int i = 0; i < tabDoc->qtd; i++) {

    ImprimeDoc(tabDoc->documentos[i]);
  }
}

/*********** Funcoes especificas do programa dois *****************/

tTabelaDocumento_pt AlocaTabelaDocLeitura(int numDocs) {

  tTabelaDocumento_pt tabela =
      (tTabelaDocumento_pt)malloc(sizeof(tTabelaDocumento));
  tabela->documentos = (tDocumento_pt *)malloc(sizeof(tDocumento_pt) * numDocs);

  return tabela;
}

tTabelaDocumento_pt CriaTabelaDocLeitura(int numDocs) {

  tTabelaDocumento_pt tabela = AlocaTabelaDocLeitura(numDocs);
  tabela->max = numDocs;
  tabela->qtd = numDocs;

  for (int i = 0; i < numDocs; i++) {
    tabela->documentos[i] = CriaDocLeitura(i);
  }

  return tabela;
}

void AddNomeTabelaDocLeitura(tTabelaDocumento_pt tabela, char *nome,
                             int indice) {
  strcpy(RetornaNomeDoc(tabela->documentos[indice]), nome);
}

void AddTipoTabelaLeitura(tTabelaDocumento_pt tabela, char *tipo, int indice) {
  strcpy(RetornaTipoDoc(tabela->documentos[indice]), tipo);
}

void AddQtdInfoDocTabelaLeitura(tTabelaDocumento_pt tabela, int qtdInfo,
                                int indice) {
  AddQtdInfoDocLeitura(tabela->documentos[indice], qtdInfo);
}

void addPropTabelaDocLeitura(tTabelaDocumento_pt tabela, int indiceD, int doc,
                             int frequencia, float tfidf, int indice) {
  AddPropDocLeitura(tabela->documentos[indiceD], doc, frequencia, tfidf,
                    indice);
}

tDocumento_pt RetornaDocNaPosicaoX(tTabelaDocumento_pt tab, int indice) {
  return tab->documentos[indice];
}

void RelatorioDoc(tTabelaDocumento_pt tabela) {

  int indice = 0, freqTotal = 0;
  int qtdDoc = RetornaQtdDoc(tabela);
  char*tipo;

  qsort(tabela->documentos, tabela->qtd, sizeof(tDocumento_pt),
        comparaDocMenor);

  printf("\nEsses sao os 10 documentos mais longos:\n\n");

  for (int i = qtdDoc - 1; i > qtdDoc - 11; i--) {
    indice = RetornaIndiceDoc(tabela->documentos[i]);
    tipo = RetornaTipoDoc(tabela->documentos[i]);
    freqTotal = RetornaFreqTotal(tabela->documentos[i]);
    printf("Documento %d com %d palavras e de classe %s\n", indice, freqTotal,
           tipo);
  }

  printf("\nEsses sao os 10 documentos mais curtos:\n\n");

  freqTotal = 0;
  for (int i = 0; i < 10; i++) {
    indice = RetornaIndiceDoc(tabela->documentos[i]);
    tipo = RetornaTipoDoc(tabela->documentos[i]);
    freqTotal = RetornaFreqTotal(tabela->documentos[i]);
    printf("Documento %d com %d palavras e de classe %s\n", indice, freqTotal,
           tipo);
  }
}

int comparaDocMenor(const void *documento1, const void *documento2) {

  tDocumento_pt doc1 = *(tDocumento_pt *)documento1;
  tDocumento_pt doc2 = *(tDocumento_pt *)documento2;

  return RetornaFreqTotal(doc1) - RetornaFreqTotal(doc2);
}

void ClassificarNoticia(tTabelaDocumento_pt tabDoc, int k,
                        tTabelaPalavra_pt tabP) {

  char *texto = (char *)malloc(sizeof(char) * 10000);
  
  printf("\nDigite o texto:\n");
  fgets(texto, 10000, stdin);

  int tamanho = strlen(texto);
  texto[tamanho - 1] = '\0';
  char *textoCpy = (char *)malloc(sizeof(char) * tamanho);
  strcpy(textoCpy, texto);

  char *textoCpy2 = (char *)malloc(sizeof(char) * tamanho);
  strcpy(textoCpy2, texto);

  int qtdWord = QtdDepalavras(textoCpy);
  char **listaWord = QuebraTexto(texto, textoCpy2);

  tPropriedade_pt *vetorP = AlocaPropriedadeLeitura(qtdWord);
  AlocaPropriedade_pt(vetorP, qtdWord);
  int qtdVetorP = 0, indiceP = 0;

  char *aux;

  for (int i = 0; i < qtdWord; i++) {
    for (int j = 0; j < RetornaQtdPalavra(tabP); j++) {
      aux = RetornaNomePalavra(RetornaListaWord(tabP)[j]);
      if (strcmp(listaWord[i], aux) == 0) {

        int achou = 0;
        indiceP = RetornaIndicePalavra(RetornaListaWord(tabP)[j]);

        for (int a = 0; a < qtdVetorP; a++) {

          if (indiceP == RetornaDocPropriedade(vetorP[a])) {

            IncrementaFrequencia(vetorP[a]);
            achou = 1;
          }
        }
        if (achou == 0) {
          AddPalavraFreq(vetorP[qtdVetorP], indiceP, 1);
          qtdVetorP++;
        }
      }
    }
  }

  int vDocsAparece[tabDoc->qtd];

  for (int i = 0; i < tabDoc->qtd; i++) {
    vDocsAparece[i] = -1;
  }
  int qtdVetorDocs = 0;

  for (int i = 0; i < qtdVetorP; i++) {

    int docAparece = 0;

    for (int j = 0; j < RetornaQtdPalavra(tabP); j++) {

      int indicePalavra = j;
      int indicePalavraP = RetornaDocPropriedade(vetorP[i]);

      if (indicePalavra == indicePalavraP) {

        docAparece = RetornaQtdInfosPalavra(RetornaPalavraPosicaoX(tabP, j));

        for (int a = 0;
             a < RetornaQtdInfosPalavra(RetornaPalavraPosicaoX(tabP, j)); a++) {
          int igual = 0;
          for (int c = 0; c < qtdVetorDocs; c++) {
            if (RetornaDocPropriedade(RetornaPropiedadePalavra(
                    RetornaPalavraPosicaoX(tabP, j))[a]) == vDocsAparece[c]) {
              igual = 1;
            }
          }
          if (igual == 0) {
            vDocsAparece[qtdVetorDocs] = RetornaDocPropriedade(
                RetornaPropiedadePalavra(RetornaPalavraPosicaoX(tabP, j))[a]);
            qtdVetorDocs++;
          }
        }
        docAparece = RetornaQtdInfosPalavra(RetornaPalavraPosicaoX(tabP, j));
      }
    }
    CalculaTfidf(vetorP[i], tabDoc->qtd + 1, docAparece);
  }

  tPropriedade_pt *vCossenos = AlocaPropriedadeLeitura(qtdVetorDocs);
  for (int i = 0; i < qtdVetorDocs; i++) {

    vCossenos[i] = InicializaPropDoc(
        vDocsAparece[i], 0,
        CalculaCosseno(vetorP, qtdVetorP,
                       RetornaDocNaPosicaoX(tabDoc, vDocsAparece[i])));
  }

  select_sort(vCossenos, qtdVetorDocs);

 
  

  printf(
      "\nEssas sao os %d documentos mais parecidos com o texto digitado:\n\n",
      k);

  int doc = 0;
  int vTipos[k];
  int frequencias[k];
  int qtdTipos = 0;
  int igual = 0;



  for (int i = 0; i < k; i++) {

    if(i>qtdVetorDocs-1){
      break;
    }
    doc = RetornaDocPropriedade(vCossenos[qtdVetorDocs-1-i]);
    for (int j = 0; j < qtdTipos; j++) {
      if (strcmp(RetornaTipoDoc(tabDoc->documentos[doc]),
                 RetornaTipoDoc(RetornaDocNaPosicaoX(tabDoc, vTipos[j]))) ==
          0) {
            

        frequencias[j]++;
        igual = 1;
      }
    }

    if (igual == 0) {
      vTipos[qtdTipos] = doc;
      frequencias[qtdTipos] = 1;
      qtdTipos++;
    }
  
    printf("documento: %d %s\n", doc, RetornaTipoDoc(tabDoc->documentos[doc]));
  }

  int maiorFreq = 0;
  int tipoFrequente=0;
  for (int i = 0; i < qtdTipos; i++) {

    
    if (frequencias[i] > maiorFreq) {
      maiorFreq = frequencias[i];
      tipoFrequente = vTipos[i];
      
    }
  }
  printf("\nclasse sugerida para esse documento: %s\n",
         RetornaTipoDoc(RetornaDocNaPosicaoX(tabDoc, tipoFrequente)));

  LiberaPropriedades(vCossenos, qtdVetorDocs);
  LiberaPropriedades(vetorP, qtdWord);

  for (int i = 0; i < qtdWord; i++) {
    free(listaWord[i]);
  }
  free(listaWord);

  free(textoCpy2);
  free(textoCpy);
  free(texto);
}

tTabelaDocumento_pt LeituraArqBinD(FILE *arq, char *nome) {

  tTabelaDocumento_pt tabelaDoc;

  int tamanho = 0, qtdInfo = 0, documento = 0, frequencia = 0, qtdDoc = 0;

  float tfidf = 0.0;
  char tipo[4];

  if (arq) {
    fread(&qtdDoc, sizeof(int), 1, arq);

    tabelaDoc = CriaTabelaDocLeitura(qtdDoc);

    for (int i = 0; i < qtdDoc; i++) {
      fread(&tamanho, sizeof(int), 1, arq);

      fread(nome, sizeof(char) * tamanho, 1, arq);
      nome[tamanho] = '\0';
      AddNomeTabelaDocLeitura(tabelaDoc, nome, i);

      fread(tipo, sizeof(char) * 4, 1, arq);
      AddTipoTabelaLeitura(tabelaDoc, tipo, i);

      fread(&qtdInfo, sizeof(int), 1, arq);
      AddQtdInfoDocTabelaLeitura(tabelaDoc, qtdInfo, i);

      for (int j = 0; j < qtdInfo; j++) {
        fread(&documento, sizeof(int), 1, arq);
        fread(&frequencia, sizeof(int), 1, arq);
        fread(&tfidf, sizeof(float), 1, arq);
        
        addPropTabelaDocLeitura(tabelaDoc, i, documento, frequencia, tfidf, j);
      }
    }
  } else {
    printf("Erro ao abrir o arquivo!\n");
  }

  return tabelaDoc;
}

void AddFreqTotalTabela(tTabelaDocumento_pt tabela) {

  for (int i = 0; i < tabela->qtd; i++)
    CalculaFreqTotal(tabela->documentos[i]);
}



