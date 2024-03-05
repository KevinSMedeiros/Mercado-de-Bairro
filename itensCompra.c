#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "itensCompra.h"


/**
 * Verifica a quantidade itens comprados registrados 
 * @return Retorna a quantidade itens comprados registrados registrados no arquivo
*/
int quantidadeItensCompraCSV()
{
    char nomeArquivo[] = "ItensCompras.csv";
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

/**
 * Faz a leitura do arquivo ItensCompras.csv e carrega 
 * as informações na lista utilizada como parâmetro
 * @param lista Ponteiro para o vetor que armazena a lista de ITENS_COMPRA realizadas
 * @return Retorna a quantidade de itens_compras lidas
*/
int lerItensCompraCSV(ITENS_COMPRA *lista )
{
    char nomeArquivo[] = "ItensCompras.csv";
    FILE *csv;
    char linha[1000];
    char *campos;
    const char s[2] = ";";
    int contadorLinha = 0;
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // fim dos registros, reabrindo para ler os dados
        fseek(csv, 0, SEEK_SET);
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        // alocando memoria para os registros lidos

        int i = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            // separando os dados de uma linha
            campos = strtok(linha, s);
            int campoAtual = 0;
            while (campos != NULL)
            {
                printf(" %s\n", campos);
                switch (campoAtual)
                {
                    case IDVEND_ITENS:
                        lista[i].idVenda = atoi(campos);
                        break;
                    case CPF_ITENS:
                        strcpy(lista[i].CPF, campos);
                        break;
                    case IDPROD__ITENS:
                        lista[i].idProduto  = atoi(campos);;
                        break;
                    case QUANT_ITENS:
                        lista[i].quantidade = atoi(campos);
                        break;
                    case PRECOUNIT_ITENS:
                        lista[i].precoUnitario = atof(campos);
                        break;
                    case PRECOTOTAL_ITENS:
                        lista[i].precoTotal = atof(campos);
                    default:
                        break;
                }
                campos = strtok(NULL, s);
                campoAtual++;
            }
            i++;
            // dados do setor;
        }
        contadorLinha = i;
        return contadorLinha;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }
}
void cadastrarItensCompra(int quantidade, int idProduto, char cpf[13]){
    char nomeArquivo[] = "ItensCompra.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "a");

    if (csv == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "w");
        fprintf(csv, "idVenda;cpf;idProduto;quantidade;precoUnitario;precoTotal\n");
        fflush(csv);
    }
}
