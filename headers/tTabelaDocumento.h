typedef struct tTabelaDocumento tTabelaDocumento;
typedef tTabelaDocumento *tTabelaDocumento_pt;

#ifndef _TTABELADOCUMENTO_H_
#define _TTABELADOCUMENTO_H_
#include "util.h"
#include "tTabelaPalavra.h"
#include "tDocumento.h"
#include "tPropriedade.h"

/**
 * @brief Faz um malloc do tamanho da tabela de Documento, na lista  de documentos e inicializa os valores de qtd e max de documentos;
 * 
 * @return tTabelaDocumento_pt 
 */
tTabelaDocumento_pt CriaTabelaDoc();


/**
 * @brief Adiciona um novo documento na tabela e incrementa a quantidade de documentos. Quando necessario faz realloc;
 * 
 * @param tabDoc 
 * @param doc 
 */
void AddDocNaTabela(tTabelaDocumento_pt tabDoc, tDocumento_pt doc);

/**
 * @brief Nessa funcao retornamos as informacoes de cada palavra da nossa tabela para que ela seja armazenada nas infos dos documentos em que ela aparece; 
 * 
 * @param tabPalavra 
 * @param tabDoc 
 */
void AddPalavrasTabelaDoc(tTabelaPalavra_pt, tTabelaDocumento_pt);

/**
 * @brief Dobra o valor maximo de documentos e realloc com esse novo valor;
 * 
 * @param tab 
 */
void RealocaTabelaDoc(tTabelaDocumento_pt tab);


/**
 * @brief Abre um FILE* com o nome do arquivo binario passado no parametro no modo "ab" para escrever no final do arquivo, e escreve todas as informacoes da tabela com a funcao fwrite;
 * 
 * @param tabela 
 * @param nomeArq 
 */
void CriaArqBinarioDoc(tTabelaDocumento_pt, char*);

/**
 * @brief faz um for de zero ate a quantidade de documento e vai chamando a funcao libera documento, depois libera o ponteiro duplo de documento e a tabela;
 * 
 * @param tabela 
 */
void LiberaTabelaDoc(tTabelaDocumento_pt);

/**
 * @brief Retorna a quantidade de documentos da tabela;
 * 
 * @param tabela 
 * @return int 
 */
int RetornaQtdDoc(tTabelaDocumento_pt);

void ImprimeTabelaDoc(tTabelaDocumento_pt tab);

/*********** Funcoes especificas do programa dois *****************/

/**
 * @brief Aloca uma tabela de documentos ja com o numero certo de documentos existentes;
 * 
 * @param qtdDoc 
 * @return tTabelaDocumento_pt 
 */
tTabelaDocumento_pt AlocaTabelaDocLeitura(int);

/**
 * @brief Cria uma tabela, chama a funcao AlocaTabelaDocLeitura, inicializa os valores da quantidade e maximo de documentos e para cada documento chama a funcao CriaDocLeitura;
 * 
 * @param qtdDocs 
 * @return tTabelaDocumento_pt 
 */
tTabelaDocumento_pt CriaTabelaDocLeitura(int);

/**
 * @brief Associa o nome passado no parametro ao nome do documento na posicao indice da lista;
 * 
 * @param tabela 
 * @param nome 
 * @param indice 
 */
void AddNomeTabelaDocLeitura(tTabelaDocumento_pt, char*, int);

/**
 * @brief Associa o tipo passado no parametro ao tipo do documento na posicao indice da lista;
 * 
 * @param tabela 
 * @param tipo 
 * @param indice 
 */
void AddTipoTabelaLeitura(tTabelaDocumento_pt, char*, int);

/**
 * @brief Associa a qtdInfo passado no parametro a quantidade de informacao do documento na posicao indice da lista;
 * 
 * @param tabela 
 * @param qtdInfo 
 * @param indice 
 */
void AddQtdInfoDocTabelaLeitura(tTabelaDocumento_pt, int, int);

/**
 * @brief Chama a funcao AddPropDocLeitura para o documento da lista de posicao indice e passa seus parametros;
 * 
 * @param tabela 
 * @param indiceD 
 * @param palavra 
 * @param frequencia 
 * @param tfidf 
 * @param indice 
 */
void addPropTabelaDocLeitura(tTabelaDocumento_pt, int, int, int,float, int);

/**
 * @brief Retorna o documento da lista na posicao passada no parametro;
 * 
 * @param tab 
 * @param indice 
 * @return tDocumento_pt 
 */
tDocumento_pt RetornaDocNaPosicaoX(tTabelaDocumento_pt tab, int indice);

/**
 * @brief Usa a funcao uma vez qsort para ordenar a lista de documento de acordo com a total de frequencias do arquivo e imprime as dez primeiras e as dez ultimas posicoes;
 * 
 * @param tabela 
 */
void RelatorioDoc(tTabelaDocumento_pt tabela);

/**
 * @brief Funcao usada no qsort to relatorio documento;
 * 
 * @param documento1 
 * @param tocumento2 
 * @return int 
 */
int comparaDocMenor(const void*, const void*);

/**
 * @brief A funcao le um texto e separa suas palavras em um ponteiro duplo de char, entao comparamos se a palavra existe na tabela(se nao exitir nao vai entrar no calculo). Depois preenchemos suas propriedes(documento em que aparece, frequencia e calculamos seu tf-idf). Depois calculamos o cosseno e ordenamos o vetor, e vemos qual tipo de noticia que mais aparece;
 * 
 * @param tabelaDoc 
 * @param k 
 * @param tabelaWord 
 */
void ClassificarNoticia(tTabelaDocumento_pt, int, tTabelaPalavra_pt);

tTabelaDocumento_pt LeituraArqBinD(FILE*, char*);

void AddFreqTotalTabela(tTabelaDocumento_pt);

#endif

