#ifndef __PRODUTOS_H__
#define __PRODUTOS_H__

#include <stdio.h>
#include "tempo.h"

typedef struct PRODUTO {
    unsigned int id;
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
void gravarProdutoCSV( PRODUTO p);

void modificarProduto(); // funcao que consegue alterar informacoes numa linha no meio do arquivo

int buscarProdutoPorID(int id); //retorna o indice do produto no arquivo csv.
//pode parecer meio redundante (pq ele retorna com o mesmo parametro de entrada), mas
//essa função é importante pq precisa ver se o id existe.

int buscarProdutoPorNome(char nome[51]); //encontra e retorna com o id do produto no arquivo csv.

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

PRODUTO retornarProdutoNaLinha(int i); // recebe um inteiro que fala em qual linha buscar,
//ai ele retorna com um valor de tipo PRODUTO com todas as informacoes na linha

void mostrarProdutosComEstoqueAbaixoDe5(); // faz uma lista de nomes dos produtos que possuem menos de 5 de estoque,
//alem de mostrar a quantidade restante

void calcularEstoqueDeCadaSetor(); // conta o estoque total de todos os produtos em cada setor

void listarProdutosPorSetor();
//permite escolher um setor e o programa gera uma lista dos nomes de todos os produtos desse setor

#endif
