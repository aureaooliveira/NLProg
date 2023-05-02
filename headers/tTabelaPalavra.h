typedef struct tTabelaPalavra tTabelaPalavra;
typedef tTabelaPalavra* tTabelaPalavra_pt;

#ifndef _TTABELAPALAVRA_H_
#define _TTABELAPALAVRA_H_
#include"tTabelaDocumento.h"
#include "util.h"
#include "tDocumento.h"

typedef int (*fptrCompara)(const void*,const void*);

/**
 * @brief Da um malloc do tamanho da tabela e depois na lista de palavras;
 * 
 * @return tTabelaPalavra_pt 
 */
 tTabelaPalavra_pt AlocaTabelaPalavra();

/**
 * @brief Chama a funcao AlocaTabelaPalavra e depois incializa os valores da quantidade e maximo de palavras;
 * 
 * @return tTabelaPalavra_pt 
 */
tTabelaPalavra_pt CriaTabelaPalavra();

/**
 * @brief A funcao compara a palavra passada com todas as palavras que ja estao na tabela, se ela ja estiver na tabela sua frequencia e aumentada, caso contrario ela entra na tabela. A funcao faz realloc quando necessario. Ela retorna um int se a palavra ja estava na tabela; 
 * 
 * @param palavra 
 * @param tabela 
 * @param doc 
 * @return int 
 */
int AddPalavraNaTabela(tPalavra_pt, tTabelaPalavra_pt, tDocumento_pt);

/**
 * @brief Dobra o valor maximo e utiliza esse valor para realocar a lista de palavras;
 * 
 * @param tabela 
 */
void RealocaTabela(tTabelaPalavra_pt);

/**
 * @brief Recebe duas palavras e o retorno e o valor da strcmp entre os dois nomes;
 * 
 * @param palavra1 
 * @param palavra2 
 * @return int 
 */
int Compara(const void*, const void*);

/**
 * @brief Chama a funcao qsort para ordenar a tabela em ordem alfabetica;
 * 
 * @param tabela 
 */
void OrdenaTabela(tTabelaPalavra_pt);

/**
 * @brief faz um for com a quantidade de palavras na tabela e para a palavra da lista de posicao i recebe o valor i;
 * 
 * @param tabela 
 */
void AddIndiceTabela(tTabelaPalavra_pt);

/**
 * @brief Abre um FILE* com o nome do arquivo binario passado no parametro no modo "wb" para escrever em binario, e escreve todas as informacoes da tabela com a funcao fwrite;
 * 
 * @param tabela 
 * @param nomeArq 
 */
void CriaArqBinario(tTabelaPalavra_pt, char*);

/**
 * @brief Utiliza dois for para calcula os valores dos tf-idf para cada palavra e em cada documento; 
 * 
 * @param tab 
 * @param numNews 
 */
void AddTfidfTabelaPalavra(tTabelaPalavra_pt tab, int numNews);

/**
 * @brief Faz um for de zero ate a quantidade de palavras e chama a funcao libera palavra pra cada uma dela, depois da free no ponteiro duplo de palavras e na tabela;
 * 
 * @param tabela 
 */
void LiberaTabela(tTabelaPalavra_pt);

/**
 * @brief Retorna o ponteiro duplo que representa a lista de palavras da tabela;
 * 
 * @param tabela 
 * @return tPalavra_pt* 
 */
tPalavra_pt *RetornaListaWord(tTabelaPalavra_pt);

/**
 * @brief Retorna o maximo de informacao da tabela;
 * 
 * @param tabela 
 * @return int 
 */
int RetornaMaxPalavra(tTabelaPalavra_pt);

/**
 * @brief Retorna a quantidade de palavras da tabela;
 * 
 * @param tabela 
 * @return int 
 */
int RetornaQtdPalavra(tTabelaPalavra_pt);

/**
 * @brief Retorna a palavra da posicao do indice passado no parametro;
 * 
 * @param tabela 
 * @param indice 
 * @return tPalavra_pt 
 */
tPalavra_pt RetornaPalavraPosicaoX(tTabelaPalavra_pt,int);

void ImprimeTabelaPalavra(tTabelaPalavra_pt);

/*********** Funcoes especificas do programa dois *****************/

/**
 * @brief Aloca a tabela de palavras ja do tamanho da quantidade de palavras passada no parametro;
 * 
 * @param qtdWord 
 * @return tTabelaPalavra_pt 
 */
tTabelaPalavra_pt AlocaTabelaPalavraLeitura(int);

/**
 * @brief Cria a tabela e chama a funcao AlocaTabelaPalavraLeitura, inicializa os valor de quantidade e maximo da tabela, faz um looping para criar cada palavra usando a funcao CriaPalavraLeitura e adiciona o indice da palavra;
 * 
 * @param qtdWord 
 * @return tTabelaPalavra_pt 
 */
tTabelaPalavra_pt CriaTabelaPalavraLeitura(int);

/**
 * @brief Chama a funcao AddNomePalavraLeitura passando a palavra da tabela no indice dado e o nome;
 * 
 * @param tabela 
 * @param nome 
 * @param indice 
 */
void AddNomeTabelaLeitura(tTabelaPalavra_pt, char*, int);

/**
 * @brief Chama a funcao AddQtdInfoPalavraLeitura passando a palavra no indice dado e a qtdInfo;
 * 
 * @param tabela 
 * @param indice 
 * @param qtdInfo 
 */
void AddQtdInfoTabelaLeitura(tTabelaPalavra_pt, int, int);

/**
 * @brief Chama a funcao AddPropriedadesPalavraLeitura passando a palavra da tabela no indice outro indice para saber em que propriedade colocar as informacoes e os valores do doc, frequencia e tf-idf;
 * 
 * @param tabela 
 * @param IndiceP 
 * @param doc 
 * @param frequencia 
 * @param indice 
 * @param tfidf 
 */
void AddPropriedadesTabelaLeitura(tTabelaPalavra_pt, int, int, int, int,float);

/**
 * @brief A funcao le um texto e separa as palavras que ficam armazenadas em um ponteiro duplo de char, depois comparamos as palavras achadas com as palavras da tabela(se nao achar nada printa que a palavra nao foi encontrada). Criamos um vetor float com o numero de documentos do arquivo e para todas as palavras achadas somamos o seu tfidf na posicao do documento ao qual ela pertence, depois ordena o vetor junto com outro vetor de indices(para nao se perder o indice de cada tf-idf). Entao printamos os indices de documentos ordenados e damos free nos vetores que alocamos;
 * 
 * @param tabela 
 * @param qtdDoc 
 */
void BuscarPalavras(tTabelaPalavra_pt, int);

/**
 * @brief A funcao le uma palavra, depois comparamos essa palavra com todas da tabela(se na achar printa que a palavra nao foi encontrada). Se ela foi encontrada printamos em quantos documentos ela aparece. Depois usamos qsort para ordernar de acordo com a frequencia e depois printamos os dez primeiro(se houver 10 ou mais documentos, caso contratrio so printamos os existentes);
 * 
 * @param tabelaWord 
 * @param tabelaDoc 
 */
void RelatorioPalavra(tTabelaPalavra_pt tabela, tTabelaDocumento_pt);

/**
 * @brief Recebe um FILE* que foi aberto na main no modo "rb" para ler em binario, e le todas as informacoes da tabela com a funcao fread;
 * 
 * @param arq 
 * @param nome 
 * @return tTabelaPalavra_pt 
 */
tTabelaPalavra_pt LeituraArqBinP(FILE*, char*);

#endif

