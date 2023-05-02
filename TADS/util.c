#include "util.h"

int QtdDepalavras(char *texto){
  
  int qtdWord = 0;
  
  if (qtdWord == 0) {
    if (strtok(texto, " ") != NULL)
      qtdWord++;
  }

  while (strtok(NULL, " ") != NULL)
    qtdWord++;
  
  return qtdWord;
}

char **QuebraTexto(char *texto, char *textoCpy) {

  int tamanho = 0;
  tamanho = strlen(texto);
  
  int numWords = QtdDepalavras(texto);

  char **listaPalavras = (char **)malloc(sizeof(char *) * numWords);

  char *save = NULL;
  char *aux = strtok_r(textoCpy, " ", &save);

  for (int i = 0; i < numWords; i++) {
    if (i == 0) {
      tamanho = strlen(aux);
      listaPalavras[i] = (char *)malloc(sizeof(char) * (tamanho + 1));
      strcpy(listaPalavras[i], aux);
    } else {
      aux = strtok_r(NULL, " ", &save);

      if (aux != NULL) {
        tamanho = strlen(aux);
        listaPalavras[i] = (char *)malloc(sizeof(char) * (tamanho + 1));
        strcpy(listaPalavras[i], aux);
      }
    }
  }
  
  return listaPalavras;
}