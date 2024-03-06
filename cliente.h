#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "tempo.h"

typedef struct CLIENTE
{
    char CPF[15];
    char nome[51];
    DATA dataNascimento;
    int idade;
    char endereco[101];
    char cidade[101];
    char estado[3];
    int pontos;
} CLIENTE;


/**
 * Retorna a quantidade de clientes existentes no cadastro
 * @return Quantidade de clientes encontrados no cadastro
*/
int quantidadeClientesCSV();

/**
 * Função que exibe os dados de um cliente
 * @param c Registo com os dados de um cliente
*/
void exibirCliente(CLIENTE c);

/**
 * Gravando os dados de um cliente no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param c Cliente que será salvo no registro
*/
void cadastrarCliente(CLIENTE c);
void interfaceCadastrarCliente(CLIENTE novoCliente);

CLIENTE retornarClienteNaLinha(int indiceDesejado); // recebe um inteiro que fala em qual linha buscar,
//ai ele retorna com um valor de tipo CLIENTE com todas as informacoes na linha

int buscarClientePorCPF(char cpf[15]); //encontra e retorna com o id do cliente no arquivo csv.

int buscarClientePorNome(char cpf[51]); //encontra e retorna com o id do cliente no arquivo csv.

void mostrarNomesComMaisDeMilPontos(); // gera uma lista de nomes dos clientes com mais de 1000 pontos

int quantosClientesEntre18e25(); // calcula o numero de clientes entre 18 e 25 anos.

void modificarCliente(CLIENTE c, int indice); // funcao que consegue alterar informacoes numa linha no meio do arquivo
void interfaceModificarCliente();

#endif
