#ifndef __ITENS_COMPRA_H__
#define __ITENS_COMPRA_H__

enum CAMPOS_ITENS_COMPRA {IDVEND_ITENS = 0, CPF_ITENS, IDPROD__ITENS, QUANT_ITENS, PRECOUNIT_ITENS, PRECOTOTAL_ITENS};


typedef struct ITENS_COMPRA
{
    /* Identificação da venda */
    unsigned int idVenda;
    /* CPF do cliente que fez a venda*/
    char CPF[14];
    /* Identificação do produto */
    unsigned int idProduto;
    /* Quantidade de produtos comprados */
    int quantidade;
    /* Preço unitário do produto que foi comprado*/
    float precoUnitario;
    /* Preço total considerando preço unitário e quantidade */
    float precoTotal;
} ITENS_COMPRA;


/**
 * Verifica a quantidade itens comprados registrados 
 * @return Retorna a quantidade itens comprados registrados registrados no arquivo
*/
int quantidadeItensCompraCSV();

/**
 * Faz a leitura do arquivo ItensCompras.csv e carrega 
 * as informações na lista utilizada como parâmetro
 * @param lista Ponteiro para o vetor que armazena a lista de ITENS_COMPRA realizadas
 * @return Retorna a quantidade de itens_compras lidas
*/
int lerItensCompraCSV(ITENS_COMPRA *lista );

void gravarItensCompraCSV(int idVenda, int quantidade, int idProduto, double precoUnitario, char cpf[14]);


#endif