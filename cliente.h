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

void cadastrarCliente(CLIENTE c);

CLIENTE retornarClienteNaLinha(int indiceDesejado);


void buscarClientePorCPF(char cpf[15]);

void buscarClientePorNome(char cpf[51]);

void mostrarNomesComMaisDeMilPontos();

int quantosClientesEntre18e25();


#endif
