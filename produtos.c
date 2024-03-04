#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "produtos.h"


unsigned int obterProximoIdProduto()
{
    FILE *arquivo;
    arquivo = fopen("Produtos.csv", "r");

    unsigned int ultimoId = 0;
    unsigned int proximoId = 1;
    char linha[100];

    if (arquivo != NULL)
    {

        while (fgets(linha, sizeof(linha), arquivo) != NULL)
        {
            sscanf(linha, "%u", &ultimoId);
        }
        proximoId = ultimoId + 1;
        fclose(arquivo);
    }

    return proximoId;
}

int gravarProdutoCSV(PRODUTO p)
{
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "a");

    if (csv == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "w");
        fprintf(csv, "id;setor;nome;preco;data de validade;estoque\n");
        fflush(csv);
    }

    fseek(csv, 0, SEEK_END); // arquivo ja existe, insere apenas o dado no final do arquivo

    if (ftell(csv) == 0)
    {
        //ftell pega a posicao do cursor. se o seek_end deu na posicao 0, significa que o arquivo ta vazio, ai escreve o cabecalho
        fprintf(csv, "id;setor;nome;preco;data de validade;estoque\n");
    }

    fprintf(csv, "%d;%s;%s;%.2f;%02d/%02d/%04d;%d\n", p.id, p.setor, p.nome, p.preco, p.dataValidade.dia, p.dataValidade.mes, p.dataValidade.ano, p.estoque);

    fflush(csv);
    fclose(csv);
}

void exibirProduto(PRODUTO p)
{
    printf("Exibindo um produto \n");
    printf("Idenficador do produto: ");
    printf(" %u\n", p.id);
    printf("Setor do produto :  ");
    printf(" %s\n", p.setor);
    printf("Nome do produto: ");
    printf(" %s\n", p.nome);
    printf("Preço do produto: ");
    printf(" %.2f\n", p.preco);
    printf("Data de Validade: %02d/%02d/%04d\n",p.dataValidade.dia, p.dataValidade.mes, p.dataValidade.ano);
    printf("Estoque do produto: ");
    printf(" %i\n", p.estoque);
}

PRODUTO retornarProdutoNaLinha(int indiceDesejado)
{
    PRODUTO produto;
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r");

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), csv);  //faz pular o cabecalho

    int indiceAtual = 1;

    while (fscanf(csv, "%d;%[^;];%[^;];%f;%d/%d/%d;%d\n", &produto.id, produto.setor, produto.nome, &produto.preco, &produto.dataValidade.dia, &produto.dataValidade.mes, &produto.dataValidade.ano, &produto.estoque) == 8)
    {
        if (indiceDesejado == indiceAtual)
        {
            fclose(csv);
            return produto;
        }
        indiceAtual = indiceAtual + 1;
    }

    exit(1);
}

int buscarProdutoPorID(int id)
{
    int i;
    PRODUTO produto;

    int encontrou = 0;

    for(i = 1; i <= quantidadeProdutosCSV(); i++)
    {
        produto = retornarProdutoNaLinha(i);
        if(produto.id == id)
        {
            printf("\n%s", produto.id);
            encontrou = 1;
            return i;
            //retorna a linha do produto no arquivo csv
        }
    }
    if(encontrou == 0)
    {
        printf("nao tem produtos com esse id");
    }
}

int buscarProdutoPorNome(char nome[51])
{
    int i;
    PRODUTO produto;

    int encontrou = 0;

    for(i = 1; i <= quantidadeProdutosCSV(); i++)
    {
        produto = retornarProdutoNaLinha(i);
        if(strcmp(produto.nome, nome) == 0)
        {
            printf("\n%s", produto.nome);
            encontrou = 1;
            return i;
            //retorna a linha do produto no arquivo csv
        }
    }
    if(encontrou == 0)
    {
        printf("nao tem clientes com esse cpf");
    }
}

void mostrarProdutosComEstoqueAbaixoDe5()
{
    int i;
    PRODUTO produto;

    printf("\n### PRODUTOS COM ESTOQUE ABAIXO DE 5 ###\n");

    for(i = 1; i <= quantidadeProdutosCSV(); i++)
    {
        produto = retornarProdutoNaLinha(i);
        if(produto.estoque < 5)
        {
            printf("\n%s, %d restantes", produto.nome, produto.estoque);
        }
    }
}

int quantidadeProdutosCSV()
{
    char nomeArquivo[] = "Produtos.csv";
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
