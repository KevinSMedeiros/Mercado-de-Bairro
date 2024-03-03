#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cliente.h"

void cadastrarCliente(CLIENTE c)
{
    char nomeArquivo[] = "Clientes.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "a");

    if (csv == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "w");
        fprintf(csv, "CPF;Nome;Nascimento;Idade;Endereco;Cidade;Estado;pontos\n");
        fflush(csv);

    }
    // arquivo já existe, verifica se está vazio
    fseek(csv, 0, SEEK_END); // arquivo ja existe, insere apenas o dado no final do arquivo

    if (ftell(csv) == 0)
    {
        //ftell pega a posicao do cursor. se o seek_end deu na posicao 0, significa que o arquivo ta vazio, ai escreve o cabecalho
        fprintf(csv, "CPF;Nome;Nascimento;Idade;Endereco;Cidade;Estado;pontos\n");
    }

    fprintf(csv, "%s;%s;%02d/%02d/%04d;%d;%s;%s;%s;%d\n", c.CPF, c.nome, c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano, c.idade, c.endereco, c.cidade, c.estado, c.pontos);

    fflush(csv);
    fclose(csv);
}

void exibirCliente(CLIENTE c)
{
    printf("\n######################################\n");
    printf("CPF: %s\n", c.CPF);
    printf("Nome: %s\n", c.nome);
    printf("Data de Nascimento: %02d/%02d/%04d\n",c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano);
    printf("Idade: %d\n", c.idade );
    printf("Endereço: %s\n", c.endereco);
    printf("Cidade/Estado: %s-%s\n", c.cidade, c.estado);
    printf("Pontos: %d\n", c.pontos);
    printf("######################################\n");
}

CLIENTE retornarClienteNaLinha(int indiceDesejado)
{
    CLIENTE cliente;
    char nomeArquivo[] = "Clientes.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r");

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), csv); //faz pular o cabecalho

    int indiceAtual = 1;

    while (fscanf(csv, "%[^;];%[^;];%d/%d/%d;%d;%[^;];%[^;];%[^;];%d\n", cliente.CPF, cliente.nome, &cliente.dataNascimento.dia, &cliente.dataNascimento.mes, &cliente.dataNascimento.ano, &cliente.idade, cliente.endereco, cliente.cidade, cliente.estado, &cliente.pontos) == 10)
    {
        if (indiceDesejado == indiceAtual)
        {
            fclose(csv);
            return cliente;
        }
        indiceAtual = indiceAtual + 1;
    }

    exit(1);
}

void buscarClientePorCPF(char cpf[15])
{
    int i;
    CLIENTE cliente;

    int contCPF = 0;

    for(i = 1; i <= quantidadeClientesCSV(); i++)
    {
        cliente = retornarClienteNaLinha(i);
        if(strcmp(cliente.CPF, cpf) == 0)
        {
            printf("\n%s", cliente.nome);
            contCPF = contCPF + 1;
        }
    }
    if(contCPF == 0)
    {
        printf("nao tem clientes com esse cpf");
    }
}

void buscarClientePorNome(char nome[51])
{
    int i;
    CLIENTE cliente;

    int contCPF = 0;

    for(i = 1; i <= quantidadeClientesCSV(); i++)
    {
        cliente = retornarClienteNaLinha(i);
        if(strcmp(cliente.nome, nome) == 0)
        {
            printf("\n%s", cliente.nome);
            contCPF = contCPF + 1;
        }
    }
    if(contCPF == 0)
    {
        printf("nao tem clientes com esse nome");
    }
}

void mostrarNomesComMaisDeMilPontos()
{
    int i;
    CLIENTE cliente;

    printf("\n### CLIENTES COM MAIS DE 1000 PONTOS ###\n");

    for(i = 1; i <= quantidadeClientesCSV(); i++)
    {
        cliente = retornarClienteNaLinha(i);
        if(cliente.pontos > 1000)
        {
            printf("\n%s", cliente.nome);
        }
    }
}

int quantosClientesEntre18e25()
{
    int i;
    CLIENTE cliente;

    int contClientes = 0;

    for(i = 1; i <= quantidadeClientesCSV(); i++)
    {
        cliente = retornarClienteNaLinha(i);
        if(cliente.idade >= 18 && cliente.idade <= 25)
        {
            contClientes = contClientes + 1;
        }
    }

    return contClientes;
}

int quantidadeClientesCSV()
{
    char nomeArquivo[] = "Clientes.csv";
    FILE *csv;
    char linha[1000];
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        int contadorLinha = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            contadorLinha++;
        }
        fclose(csv);
        return contadorLinha;
    }
    else
    {
        // arquivo não existe
        return 0;
    }
}

void AdicionarPontosCliente(CLIENTE *c, int pontos)
{
    c->pontos += pontos;
}
