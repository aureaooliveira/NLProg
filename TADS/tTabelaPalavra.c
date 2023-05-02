#include "tTabelaPalavra.h"

struct tTabelaPalavra {
  tPalavra_pt *word;
  int max;
  int qtd;
};

 tTabelaPalavra_pt AlocaTabelaPalavra() {
  tTabelaPalavra_pt tabela = (tTabelaPalavra_pt)malloc(sizeof(tTabelaPalavra));
  tabela->word = (tPalavra_pt *)malloc(sizeof(tPalavra_pt) * 10000);
  return tabela;
}

tTabelaPalavra_pt CriaTabelaPalavra() {
  tTabelaPalavra_pt tabela = AlocaTabelaPalavra();
  tabela->max = 10000;
  tabela->qtd = 0;
  return tabela;
}

void RealocaTabela(tTabelaPalavra_pt tabela) {

  tabela->max = tabela->max * 2;
  tabela->word =
      (tPalavra_pt *)realloc(tabela->word, sizeof(tPalavra_pt) * tabela->max);
}

int AddPalavraNaTabela(tPalavra_pt palavra, tTabelaPalavra_pt tabela, tDocumento_pt doc){

  int igual = 0;
  if (tabela->qtd >= tabela->max)
    RealocaTabela(tabela);
  
  char *nomePalavra = RetornaNomePalavra(palavra);
  if (tabela->qtd == 0) {
    tabela->word[tabela->qtd] = palavra;
    tabela->qtd++;
  } else {
    for (int i = 0; i < tabela->qtd; i++) {
      if (strcasecmp(nomePalavra,RetornaNomePalavra(tabela->word[i])) == 0) {
        AddFrequenciaPalavra(doc, tabela->word[i], palavra);
        igual = 1;
      }
    }

    if (igual == 0) {
      tabela->word[tabela->qtd] = palavra;
      tabela->qtd++;
    }
  }
  return igual;
}

void ImprimeTabelaPalavra(tTabelaPalavra_pt tabela) {

  for (int i = 0; i < tabela->qtd; i++) {

    ImprimePalavra(tabela->word[i]);
  }
  printf("todas as palavras:%d\n", tabela->qtd);
}

void LiberaTabela(tTabelaPalavra_pt tabela) {

  if (tabela != NULL) {
    for (int i = 0; i < tabela->qtd; i++) {
      LiberaPalavra(tabela->word[i]);
    }
    if (tabela->word != NULL) {
      free(tabela->word);
      tabela->word = NULL;
    }
    free(tabela);
  }
  tabela = NULL;
}

tPalavra_pt RetornaPalavraPosicaoX(tTabelaPalavra_pt tabela, int indice) {
  return tabela->word[indice];
}

int Compara(const void *p1, const void *p2) {

  tPalavra_pt *lista1 = (tPalavra_pt *)p1;
  tPalavra_pt *lista2 = (tPalavra_pt *)p2;
  return strcmp(RetornaNomePalavra(*lista1), RetornaNomePalavra(*lista2));
}

void OrdenaTabela(tTabelaPalavra_pt tabela) {

  fptrCompara comp = Compara;
  qsort(tabela->word, tabela->qtd, sizeof(tPalavra_pt), comp);
}

int RetornaQtdPalavra(tTabelaPalavra_pt tabela) { return tabela->qtd; }

void AddIndiceTabela(tTabelaPalavra_pt tabela) {

  for (int i = 0; i < tabela->qtd; i++) {
    AddIndice(tabela->word[i], i);
  }
}

void CriaArqBinario(tTabelaPalavra_pt tabela, char*nomeArq) {

  int teste = tabela->qtd;
  int tamanho = 0, qtdInfo = 0, documento = 0, frequencia = 0;
  float ifidf = 0.0;
  char nome[100];
  
  FILE *arq = fopen(nomeArq, "wb");

  fwrite(&teste, sizeof(int), 1, arq);
 
  for (int i = 0; i < tabela->qtd; i++) {
    tamanho = strlen(RetornaNomePalavra(tabela->word[i]));
    fwrite(&tamanho, sizeof(int), 1, arq);

    strcpy(nome, RetornaNomePalavra(tabela->word[i]));
    fwrite(nome, sizeof(char) * tamanho, 1, arq);

    qtdInfo = RetornaQtdInfosPalavra(tabela->word[i]);
    fwrite(&qtdInfo, sizeof(int), 1, arq);

    for (int j = 0; j < qtdInfo; j++) {
      documento =
          RetornaDocPropriedade(RetornaPropiedadePalavra(tabela->word[i])[j]);
      fwrite(&documento, sizeof(int), 1, arq);

      frequencia =
          RetornaFrequencia(RetornaPropiedadePalavra(tabela->word[i])[j]);
      fwrite(&frequencia, sizeof(int), 1, arq);

      ifidf = RetornaIfidf(RetornaPropiedadePalavra(tabela->word[i])[j]);
      fwrite(&ifidf, sizeof(float), 1, arq);
    }
  }
  

  fclose(arq);
}

tPalavra_pt *RetornaListaWord(tTabelaPalavra_pt tabela) { return tabela->word; }

void AddTfidfTabelaPalavra(tTabelaPalavra_pt tab, int numNews) {

  int qtdInfo = 0;
  
  for (int i = 0; i < tab->qtd; i++) {
    qtdInfo = RetornaQtdInfosPalavra(tab->word[i]);
    for (int a = 0; a < qtdInfo; a++) {
      CalculaTfidf(RetornaPropiedadePalavra(tab->word[i])[a],            numNews, qtdInfo);
    }
  }
}

int RetornaMaxPalavra(tTabelaPalavra_pt tabela) { return tabela->max; }

/*********** Funcoes especificas do programa dois *****************/

tTabelaPalavra_pt AlocaTabelaPalavraLeitura(int numWords) {
  tTabelaPalavra_pt tabela = (tTabelaPalavra_pt)malloc(sizeof(tTabelaPalavra));
  tabela->word = (tPalavra_pt *)malloc(sizeof(tPalavra_pt) * numWords);
  return tabela;
}

tTabelaPalavra_pt CriaTabelaPalavraLeitura(int numWords) {

  tTabelaPalavra_pt tabela = AlocaTabelaPalavraLeitura(numWords);
  tabela->qtd = numWords;
  tabela->max = numWords;

  for (int i = 0; i < numWords; i++) {
    tabela->word[i] = CriaPalavraLeitura();
    AddIndice(tabela->word[i], i);
  }
  return tabela;
}

void AddNomeTabelaLeitura(tTabelaPalavra_pt tabela, char *nome, int indice) {
  AddNomePalavraLeitura(tabela->word[indice], nome);
}

void AddQtdInfoTabelaLeitura(tTabelaPalavra_pt tabela, int indice,
                             int qtdInfo) {
  AddQtdInfoPalavraLeitura(tabela->word[indice], qtdInfo);
}

void AddPropriedadesTabelaLeitura(tTabelaPalavra_pt tabela, int indiceP,
                                  int frequencia, int documento, int indice,
                                  float tfidf) {
  AddPropriedadesPalavraLeitura(tabela->word[indice], indiceP, documento,
                                frequencia, tfidf);
}

void BuscarPalavras(tTabelaPalavra_pt tabela, int qtdDoc) {

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
  char **listaWord = QuebraTexto(texto,textoCpy2);

  char *nome;
  int *indicesSoma = (int *)malloc(sizeof(int) * qtdDoc);
  float *somaFreq = calloc(qtdDoc, sizeof(float));
  int achouAlgo = 0;

  for (int i = 0; i < qtdWord; i++) {
    for (int j = 0; j < tabela->qtd; j++) {
      nome = RetornaNomePalavra(tabela->word[j]);
      if (strcmp(listaWord[i], nome) == 0) {
        achouAlgo++;
        for (int k = 0; k < RetornaQtdInfosPalavra(tabela->word[j]); k++) {
          int indice = RetornaDocPropriedade(
              RetornaPropiedadePalavra(tabela->word[j])[k]);
          somaFreq[indice] +=
              RetornaIfidf(RetornaPropiedadePalavra(tabela->word[j])[k]);
        }
      }
    }
  }
  if (achouAlgo == 0) {
    printf("Palavras nao encontradas!\n");
  } else {
    for (int i = 0; i < qtdDoc; i++) {
      indicesSoma[i] = i;
    }
    float auxFloat = 0.0;
    int auxInt = 0;

    for (int i = 0; i < qtdDoc; i++) {
      for (int j = 0; j < qtdDoc; j++) {
        if (somaFreq[i] > somaFreq[j]) {
          auxFloat = somaFreq[i];
          somaFreq[i] = somaFreq[j];
          somaFreq[j] = auxFloat;
          auxInt = indicesSoma[i];
          indicesSoma[i] = indicesSoma[j];
          indicesSoma[j] = auxInt;
        }
      }
    }
    printf("\n");
    printf("Essas sao os dez documentos em que as palavras mais aparecem:\n\n");
    for (int i = 0; i < 10; i++) {
      if (somaFreq[i] != 0.0) {
        printf("Documento de indice: %d\n", indicesSoma[i]);
      }
    }
  }
  free(texto);
  free(textoCpy);
  free(textoCpy2);
  free(somaFreq);
  free(indicesSoma);
  for (int i = 0; i < qtdWord; i++)
    free(listaWord[i]);
  free(listaWord);
}

void RelatorioPalavra(tTabelaPalavra_pt tabela, tTabelaDocumento_pt tabDoc) {

  char *palavra = (char *)malloc(sizeof(char) * 50);
  char *palavraTabela;
  int totalDoc = 0, tamanho = 0, achou=0;

  printf("Digite a palavra:\n");
  fgets(palavra, 50, stdin);
  tamanho = strlen(palavra);
  palavra[tamanho - 1] = '\0';

  for (int i = 0; i < RetornaQtdPalavra(tabela); i++) {
    palavraTabela = RetornaNomePalavra(RetornaListaWord(tabela)[i]);
    if (strcmp(palavra, palavraTabela) == 0) {
      achou++;
      totalDoc = RetornaQtdInfosPalavra(RetornaListaWord(tabela)[i]);
      printf("A palavra '%s' aparece em %d documentos\n", palavra, totalDoc);

      qsort(RetornaPropiedadePalavra(RetornaListaWord(tabela)[i]), totalDoc,
            sizeof(tPropriedade_pt), ComparaFrequeciasVetorInfos);

      printf("\nos 10 em que ela aparece com mais frequência:\n\n");
      
      for(int a=0;a<10;a++){
        if(a < totalDoc){
          printf("Documento:%d -> %d vezes\n",RetornaDocPropriedade(RetornaPropiedadePalavra(RetornaListaWord(tabela)[i])[a]), RetornaFrequencia(RetornaPropiedadePalavra(RetornaListaWord(tabela)[i])[a]));
        }  
      }      FrequenciaPorClasse(RetornaPropiedadePalavra(RetornaListaWord(tabela)[i]),totalDoc,tabDoc);
    } 
  }
  if(achou == 0)
    printf("\nPalavra nao encontrada!\n");
  
 free(palavra);     
}

tTabelaPalavra_pt LeituraArqBinP(FILE *arq, char *nome) {

  tTabelaPalavra_pt tabela;

  int qtdWord = 0, tamanho = 0, qtdInfo = 0, documento = 0, frequencia = 0;

  float tfidf = 0.0;

  if (arq) {
    fread(&qtdWord, sizeof(int), 1, arq);

    tabela = CriaTabelaPalavraLeitura(qtdWord);

    for (int i = 0; i < qtdWord; i++) {
      fread(&tamanho, sizeof(int), 1, arq);

      fread(nome, sizeof(char) * tamanho, 1, arq);
      nome[tamanho] = '\0';
      AddNomeTabelaLeitura(tabela, nome, i);

      fread(&qtdInfo, sizeof(int), 1, arq);
      
      AddQtdInfoTabelaLeitura(tabela, i, qtdInfo);
      
      for (int j = 0; j < qtdInfo; j++) {

        fread(&documento, sizeof(int), 1, arq);

        fread(&frequencia, sizeof(int), 1, arq);

        fread(&tfidf, sizeof(float), 1, arq);

        AddPropriedadesTabelaLeitura(tabela, j, frequencia, documento, i,
                                     tfidf);
      }
    }
  } else {
    printf("Erro ao abrir o arquivo!\n");
  }

  return tabela;
}