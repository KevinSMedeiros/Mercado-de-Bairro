#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vendas.h"

/**
 * Verifica a quantidade de vendas registradas
 * @return Retorna a quantidade de vendas registradas
*/
int quantidadeVendasCSV()
{
    char nomeArquivo[] = "Vendas.csv";
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
 * Faz a leitura do arquivo vendas.csv e carrega
 * as informações na lista utilizada como parâmetro
 * @param lista Ponteiro para o vetor que armazena a lista de VENDAS realizadas
*/
int lerVendasCSV(VENDA *lista )
{
    char nomeArquivo[] = "Vendas.csv";
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
                    case ID_VENDA:
                        lista[i].id = atoi(campos);
                        break;
                    case CPF_VENDA:
                        strcpy(lista[i].CPF, campos);
                        break;
                    case DATA_VENDA:
                        StringToData(campos, &lista[i].dataCompra);
                        break;
                    case TOTAL_VENDA:
                        lista[i].valorTotal = atof(campos);
                        break;
                    case ITENS_VENDA:
                        lista[i].quantidadeItens = atoi(campos);
                        break;
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