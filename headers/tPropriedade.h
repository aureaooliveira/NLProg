typedef struct tPropriedade tPropriedade;
typedef tPropriedade *tPropriedade_pt;

#ifndef _TPROPRIEDADE_H_
#define _TPROPRIEDADE_H_
#include "tDocumento.h"
#include "tTabelaDocumento.h"
#include <math.h>

/**
 * @brief Aloca um ponteiro de ponteiro de propriedades de uma palavra;
 *
 * @return tPropriedade_pt*
 */
tPropriedade_pt *AlocaPropPalavra();

/**
 * @brief Aloca um ponteiro de ponteiro de propriedades de um documento;
 *
 * @return tPropriedade_pt*
 */
tPropriedade_pt *AlocaPropDocumento();

/**
 * @brief Da um malloc do tamanho propriedade, associa o indice do documento
 * passado no parametro ao documento da propriedade e incializa o valor da
 * freqeuncia em 1 e do tf-idf em 0;
 *
 * @param doc
 * @return tPropriedade_pt
 */
tPropriedade_pt InicializaPropPalavra(tDocumento_pt);

/**
 * @brief Faz malloc do tamanho propriedade, e inicializa as variaveis do struct
 * com os valores do parametro
 *
 * @param palavra
 * @param frequencia
 * @param tfidf
 * @return tPropriedade_pt
 */
tPropriedade_pt InicializaPropDoc(int palavra, int, float tfidf);

/**
 * @brief Se a palavra atual ja apareceu no documento incrementa sua frequencia
 * e depois da free na sua propriedade que ja havia sido alocada. Caso seja uma
 * nova palavra adiciona ela no ponteiro duplo de propriedade e incrementa a
 * qtdInfo. Quando necessario ela faz realloc;
 *
 * @param doc
 * @param palavra
 * @param palavraAtual
 */
void AddFrequenciaPalavra(tDocumento_pt doc, tPalavra_pt palavra,
                          tPalavra_pt palavraAtual);

/**
 * @brief Usa a formula passada para calcular o tf-idf da propriedade;
 *
 * @param propriedade
 * @param numDocs
 * @param docAparece
 */
void CalculaTfidf(tPropriedade_pt, int, int);

/**
 * @brief Cade ponteiro do ponteiro duplo de propriedade representa as
 * informacoes de uma palavra, essa funcao recebe uma palavra e coloca suas
 * informacoes na propriedade do documento. Quando necessario ela realoca o
 * espaco das propriedades;
 *
 * @param doc
 * @param palavra
 * @param freq
 * @param tfidf
 */
void addPalavraInfoDoc(tDocumento_pt doc, int palavra, int freq, float tfidf);

/**
 * @brief Associa os valores passados no parametro com a frequencia e o
 * documento da propriedade(No caso o documento da propriedade representa uma
 * palavra);
 *
 * @param propriedade
 * @param palavra
 * @param frequencia
 */
void AddPalavraFreq(tPropriedade_pt p, int palavra, int frequencia);

/**
 * @brief Realoca o ponteiro duplo de propriedade com a quantidade passada no
 * parametro;
 *
 * @param p
 * @param novoMax
 * @return tPropriedade_pt*
 */
tPropriedade_pt *RealocaVetorPropriedade(tPropriedade_pt *p, int novoMax);

/**
 * @brief Faz um for de zero a qtdInfo e da free em cada ponteiro do ponteiro
 * duplo e depois da free no ponteiro duplo;
 *
 * @param propriedade
 * @param qtdInfo
 */
void LiberaPropriedades(tPropriedade_pt *, int qtdInfo);

/**
 * @brief Faz um for de zero a qtdInfo e da free em cada ponteiro do ponteiro
 * duplo, sem dar free no ponteiro duplo;
 *
 * @param propriedade
 * @param qtdInfo
 */
void LiberaPropWordRepetida(tPropriedade_pt *);

/**
 * @brief Retoruna o documento da propriedade;
 *
 * @param proproedade
 * @return int
 */
int RetornaDocPropriedade(tPropriedade_pt);

/**
 * @brief Retorna a frequencia da propriedade;
 *
 * @param propriedade
 * @return int
 */
int RetornaFrequencia(tPropriedade_pt);

/**
 * @brief Retorna o tfidf da propriedade;
 *
 * @param propriedade
 * @return float
 */
float RetornaIfidf(tPropriedade_pt);

void ImprimePropPalavra(tPropriedade_pt);
void ImprimePropDoc(tPropriedade_pt);

/*********** Funcoes especificas do programa dois *****************/

/**
 * @brief Aloca o ponteiro duplo de propriedades ja com a quandidade certa que vai precisar(qtdInfo passado no parametro);
 * 
 * @param qtdInfo 
 * @return tPropriedade_pt* 
 */
tPropriedade_pt *AlocaPropriedadeLeitura(int);

/**
 * @brief faz o malloc do tamanho propriedade e associa os valores do parametro aos da propriedade; 
 * 
 * @param doc 
 * @param frequencia 
 * @param tfidf 
 * @return tPropriedade_pt 
 */
tPropriedade_pt AddPropriedadesLeitura(int, int, float);

/**
 * @brief Funcao para servir de parametro para funcao qsort, para ordenar as propriedades de acordo com o tf-idf;
 * 
 * @param p1 
 * @param p2 
 * @return int 
 */
int ComparaFrequeciasVetorInfos(const void *p1, const void *p2);


void FrequenciaPorClasse(tPropriedade_pt *p, int tamanho,
                         tTabelaDocumento_pt tab);
void IncrementaFrequencia(tPropriedade_pt);
void AlocaPropriedade_pt(tPropriedade_pt *, int);
float CalculaCosseno(tPropriedade_pt *texto, int qtdVetorP, tDocumento_pt doc);
int OrdenaCossenos(const void *cos1,const void *cos2);
int CalculaFreqTotalProp(tPropriedade_pt*, int);
void select_sort (tPropriedade_pt *a, int);
 double CalculaNormaVetor(tPropriedade_pt* prop,int num);

#endif
