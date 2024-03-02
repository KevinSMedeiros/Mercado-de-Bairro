#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "produtos.h"

void lerProduto( PRODUTO *p )
{

}

void exibirProduto(PRODUTO p)
{

}

unsigned int obterProximoIdProduto()
{
    FILE *arquivo;
    arquivo = fopen("Produtos.csv", "r");

    unsigned int ultimoId = 0;
    unsigned int proximoId = 1;
    char linha[100];

    if (arquivo != NULL) {

        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
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
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "id;setor;nome;preco;data de validade;estoque\n");
        fflush(csv);
    }

    fseek(csv, 0, SEEK_END); // arquivo ja existe, insere apenas o dado no final do arquivo
    
    fprintf(csv, "%d;%s;%s;%.2f;%02d/%02d/%04d;%d\n", p.id, p.setor, p.nome, p.preco, p.dataValidade.dia, p.dataValidade.mes, p.dataValidade.ano, p.estoque);

    fflush(csv);
    fclose(csv);
    // salvando o cabeçalho do arquivo
}

int quantidadeProdutosCSV()
{

}

int lerProdutosCSV(PRODUTO *lista)
{

}


