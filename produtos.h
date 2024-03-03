#ifndef __PRODUTOS_H__
#define __PRODUTOS_H__

#include <stdio.h>
#include "tempo.h"

typedef struct PRODUTO {
    int id;
    char setor[11];
    char nome[51];
    float preco;
    DATA dataValidade;
    int estoque;
} PRODUTO;


/**
 * Exibe os campos contidos em um registro do tipo PRODUTO
 * @param p Registro que será exibido
*/
void exibirProduto(PRODUTO p);

/**
 * Gravando os dados de um produto no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param p Produto que será salvo no registro
*/
int gravarProdutoCSV( PRODUTO p);

/**
 * Retorna a quantidade de produtos que estão salvos no arquivo CSV
 * @return Quantidade de produtos salvos
*/
int quantidadeProdutosCSV( );


/**
 * Rotina que devolve o id a ser utilizado no próximo cadastro
 * @param formato Define se é para o tipo de arquivo csv ou para o tipo dat
 * @return Retorna o próximo ID a ser utilizado. Se o formato não for definido para 
 * um dos dois válidos ("CSV" ou "DAT"), a função retorna -1.
*/
unsigned int obterProximoIdProduto();

PRODUTO retornarProdutoNaLinha(int i);

void mostrarProdutosComEstoqueAbaixoDe5();

#endif
