typedef struct tDocumento tDocumento;
typedef tDocumento* tDocumento_pt;

#ifndef _TDOCUMENTO_H_
#define _TDOCUMENTO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPalavra.h"
#include "tPropriedade.h"
#include "tTabelaPalavra.h"
#include "tTabelaDocumento.h"

/**
 * @brief Cria um documento, faz o malloc de um documento e retorna ele;
 * 
 * @return tDocumento_pt 
 */
tDocumento_pt AlocaDocumento();

/**
 * @brief Cria um documento, chama a funcao alocaDocumento(), depois separa o diretorio do tipo de noticia com o auxilio do strtok.
 * Associa o nome do documento com o diretorio, o nome do tipo, o indice com o passado como parametro. Aloca as infos com a funcao 
 * AlocaPropDocumento() e inicializa os valores da qtd e max de informacao;
 * 
 * @param diretorio string lida do arquivo que contem o diretorio e o tipo do documento;
 * @param indice representa o numero de noticia lidas;
 * 
 * @return tDocumento_pt 
 */
tDocumento_pt CriaDocumento(char *diretorio, int indice);

/**
 * @brief Funcao que recebe a nome da pasta cujo a pasta de test e train se encontram e concatena com os diretorios dos documentos dessa pasta
 * e abre esses arquivos
 * 
 * @param doc documento cujo FILE vai ser aberto e que contem o nome do documento;
 * @param link parte do diretorio que indica em que pasta ele se encontra, exemplo: "large/"
 */
void AbreDocumento(tDocumento_pt, char*);

/**
 * @brief Incrementa a qtdInfo do documento;
 * 
 * @param doc documento a ser incrementado;
 */
void AddQtdInfoDoc(tDocumento_pt);

void ImprimeDoc(tDocumento_pt);

/**
 * @brief Dobra a quantidade maxima de informacao e chama a funcao RealocaVetorPropriedade;
 * 
 * @param doc 
 */
void RealocaInfoDocumento(tDocumento_pt doc);

/**
 * @brief A funcao chama LiberaPropriedades e depois da free no tipo, no nome e no documento;
 * 
 * @param doc 
 */
void LiberaDocumento(tDocumento_pt);

/**
 * @brief Retorna o ponteiro de arquivo do documento;
 * 
 * @param doc 
 * @return FILE* 
 */
FILE* RetornaArquivoDoc(tDocumento_pt);

/**
 * @brief Retorna o nome do arquivo do documento;
 * 
 * @param doc 
 * @return char* 
 */
char* RetornaNomeDoc(tDocumento_pt);

/**
 * @brief Retorna o indice do documento;
 * 
 * @param doc 
 * @return int 
 */
int RetornaIndiceDoc(tDocumento_pt);

/**
 * @brief Retorna as Infos do documento;
 * 
 * @param doc 
 * @return tPropriedade_pt* 
 */
tPropriedade_pt* RetornaPropriedadeDoc(tDocumento_pt);

/**
 * @brief Retorna a quantidade de infos do documento;
 * 
 * @param doc 
 * @return int 
 */
int RetornaQtdInfoDoc(tDocumento_pt);

/**
 * @brief Retorna o maximo de Info do documento;
 * 
 * @param doc 
 * @return int 
 */
int RetornaMaxInfoDoc(tDocumento_pt);

/**
 * @brief Retorna o tipo da noticia do documento;
 * 
 * @param doc 
 * @return char* 
 */
char *RetornaTipoDoc(tDocumento_pt);

/*********** Funcoes especificas do programa dois *****************/

/**
 * @brief Cria e aloca um documento que vai ser lido do arquivo binario;
 * 
 * @param indice 
 * @return tDocumento_pt 
 */
tDocumento_pt CriaDocLeitura(int indice);

/**
 * @brief iguala a qtdInfo do documento com a passada no paramentro e depois da um malloc nas Infos utilizando a qtdInfos; 
 * 
 * @param doc 
 * @param qtdInfo 
 */
void AddQtdInfoDocLeitura(tDocumento_pt, int);

/**
 * @brief Chama a funcao AddPropriedadesLeitura repassando os valores do parametro, na info do documento na posicao do indice; 
 * 
 * @param doc 
 * @param palavra 
 * @param frequencia 
 * @param tfidf 
 * @param indice 
 */
void AddPropDocLeitura(tDocumento_pt, int, int, float, int);

void CalculaFreqTotal(tDocumento_pt);

int RetornaFreqTotal(tDocumento_pt);

#endif
