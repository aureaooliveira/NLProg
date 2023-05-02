typedef struct tPalavra tPalavra;
typedef tPalavra* tPalavra_pt;

#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_
#include "tDocumento.h"
#include "tPropriedade.h"
#include "tTabelaPalavra.h"

/**
 * @brief Cria uma palavra faz um malloc para o struct tPalavra e um para o nome da palavra;
 * 
 * @return tPalavra_pt 
 */
tPalavra_pt AlocaPalavra();

/**
 * @brief Cria uma palavra e chama a funcao AlocaPalavra() e AlocaPropPalavra(). Associa o nome passado no parametro
 * com o nome da palavra, inicializa a info[0] utilizando a funcao InicializaPropPalavra e inicializa a qtd e o max de info;
 * 
 * @param nome 
 * @param doc 
 * @return tPalavra_pt 
 */
tPalavra_pt CriaPalavra(char *nome,tDocumento_pt doc);

/**
 * @brief A funcao le todas as palavras do documento, chama a funcao CriaPalavra e AddPalavraNaTabela, caso 
 * seja uma palavra repetida ela vai ser liberada pela funcao LiberaPalavraRepetida;
 * 
 * @param tabela 
 * @param doc 
 */
void LeEPreenchePalavras(tTabelaPalavra_pt,tDocumento_pt);

void ImprimePalavra(tPalavra_pt);

/**
 * @brief Associa o indice passado no parametro com o indice da palavra;
 * 
 * @param palavra 
 * @param indice 
 */
void AddIndice(tPalavra_pt, int);

/**
 * @brief Incrementa a qtdInfo da palavra;
 * 
 * @param palavra 
 */
void AddQtdInfoPalavra(tPalavra_pt);


/**
 * @brief Dobra o maximo de Info e realloc essa nova quantidade de espaco;
 * 
 * @param palavra 
 */
void RealocaPalavra(tPalavra_pt p);

/**
 * @brief Da free no nome da palavra, chama a funcao LiberaPropriedades e da free na palavra;
 * 
 * @param palavra 
 */
void LiberaPalavra(tPalavra_pt);

/**
 * @brief Da free no nome da palavra, nas Infos e na palavra;
 * 
 * @param palavra 
 */
void LiberaPalavraRepetida(tPalavra_pt);

/**
 * @brief Retorna o indice da palavra;
 * 
 * @param palavra 
 * @return int 
 */
int RetornaIndicePalavra(tPalavra_pt);

/**
 * @brief Retorna as Infos da palavra;
 * 
 * @param palavra 
 * @return tPropriedade_pt* 
 */
tPropriedade_pt* RetornaPropiedadePalavra(tPalavra_pt);

/**
 * @brief Retorna o nome da palavra;
 * 
 * @param palavra 
 * @return char* 
 */
char* RetornaNomePalavra(tPalavra_pt);

/**
 * @brief Retorna a quantida de Infos da palavra;
 * 
 * @param palavra 
 * @return int 
 */
int RetornaQtdInfosPalavra(tPalavra_pt);

/**
 * @brief Retorna o maximo de Info da Palavra 
 * 
 * @param palavra 
 * @return int 
 */
int RetornaMaxInfosPalavra(tPalavra_pt p);

/*********** Funcoes especificas do programa dois *****************/

/**
 * @brief associa o nome do parametro ao nome da palavra com ajuda do strcpy;
 * 
 * @param palavra 
 * @param nome 
 */
void AddNomePalavraLeitura(tPalavra_pt, char*);

/**
 * @brief Cria uma palavra, chama a funcao AlocaPalavra e incializa o maxInfos(nao sera mais usado no programa 2);
 * 
 * @return tPalavra_pt 
 */
tPalavra_pt CriaPalavraLeitura();

/**
 * @brief Iguala os valores qtdInfo do parametro ao qtdInfo da palavra e depois chama a funcao AlocaPropriedadeLeitura para alocar as Infos da palavra;
 * 
 * @param palavra 
 * @param qtdInfo 
 */
void AddQtdInfoPalavraLeitura(tPalavra_pt, int);

/**
 * @brief chama a funcao AddPropriedadesLeitura para adicionar as propriedades da Info na posicao indice;
 * 
 * @param palavra 
 * @param indice 
 * @param documento 
 * @param frequencia 
 * @param tfidf 
 */
void AddPropriedadesPalavraLeitura(tPalavra_pt, int, int, int, float);

#endif
