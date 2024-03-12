#ifndef __VENDAS_H__
#define __VENDAS_H__

#include <stdio.h>
#include "tempo.h"

enum CAMPOS_VENDA {ID_VENDA=0, CPF_VENDA, DATA_VENDA, TOTAL_VENDA, ITENS_VENDA};

typedef struct VENDA
{
    /* Identificação da venda */
    unsigned int id;
    /* CPF do cliente que realizou a compra */
    char CPF[15];
    /* Data de realização da compra*/
    DATA data;
    /* Valor total da compra */
    float valorTotal;
    /* Quantidade de itens comprados, sem considerar a quantidade */
    unsigned int quantidade;
} VENDA;

/**
 * Verifica a quantidade de vendas registradas
 * @return Retorna a quantidade de vendas registradas
*/
int quantidadeVendasCSV();

/**
 * Faz a leitura do arquivo vendas.csv e carrega
 * as informações na lista utilizada como parâmetro
 * @param lista Ponteiro para o vetor que armazena a lista de VENDAS realizadas
 * @return Retorna a quantidade de vendas lidas
*/
int lerVendasCSV(VENDA *lista );
void gravarVendaCSV(VENDA venda);
int buscarVendaPorId(unsigned int id); //retorna o indice da venda no arquivo csv.
VENDA retornarVendaNaLinha(int i); // retorna com um valor de tipo VENDA relacionado as informacoes da linha solicitada
unsigned int obterProximoIdVenda(); // veri
void modificarVendas(VENDA venda); // funcao que consegue alterar informacoes numa linha no meio do arquivo
void buscaVendas(); // permite escolher se quer buscar por nome ou cpf

#endif
