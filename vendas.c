#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vendas.h"
#include "cliente.h"

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
        printf("Vendas.csv n existe");
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
                        StringToData(campos, &lista[i].data);
                        break;
                    case TOTAL_VENDA:
                        lista[i].valorTotal = atof(campos);
                        break;
                    case ITENS_VENDA:
                        lista[i].quantidade = atoi(campos);
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
unsigned int obterProximoIdVenda()
{
    FILE *arquivo;
    arquivo = fopen("Vendas.csv", "r");

    unsigned int ultimoId = 0; // tipo unsigned significa sem sinal
    unsigned int proximoId = 1;
    char linha[100];

    if (arquivo != NULL)
    {

        while (fgets(linha, sizeof(linha), arquivo) != NULL)// ele vai lendo todas as linhas, aí para quando fica nulo
        {
            sscanf(linha, "%u", &ultimoId); //%u é o especificador de sem sinal
            //sscanf procura por um valor de tipo unsigned na linha e salva em ultimoId
        }
        proximoId = ultimoId + 1;
        fclose(arquivo);
    }

    return proximoId;
}
VENDA retornarVendaNaLinha(int i){
    VENDA venda;
    char nomeArquivo[] = "Vendas.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r");

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), csv);  //faz pular o cabecalho

    int indiceAtual = 1;

    //vai passando de linha em linha ate chegar na linha que interessa, ai retorna um valor de tipo PRODUTO
    while (7 == fscanf(csv, "%d;%[^;];%d/%d/%d;%f;%d\n", &venda.id, venda.CPF, &venda.data.dia,
                       &venda.data.mes, &venda.data.ano, &venda.valorTotal, &venda.quantidade))
    {
        if (i == indiceAtual)
        {
            fclose(csv);
            return venda;
        }
        indiceAtual = indiceAtual + 1;

    }

    exit(1);
}

void gravarVendaCSV(VENDA venda) {
    char nomeArquivo[] = "Vendas.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "a");

    if (csv == NULL) {
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "w");
        fprintf(csv, "id;cpf;data;valorTotal;quantidadeProdutos\n");
        fflush(csv);
    }

    fseek(csv, 0, SEEK_END); // arquivo ja existe, insere apenas o dado no final do arquivo

    if (ftell(csv) == 0)
    {
        //ftell pega a posicao do cursor. se o seek_end deu na posicao 0, significa que o arquivo ta vazio, ai escreve o cabecalho
        fprintf(csv, "id;cpf;data;valorTotal;quantidadeProdutos\n");
    }
    venda.data = hoje();
    fprintf(csv, "%d;%s;%02d/%02d/%04d;%.2f;%d\n", venda.id, venda.CPF,  venda.data.dia, venda.data.mes, venda.data.ano,venda.valorTotal, venda.quantidade);

    fflush(csv);
    fclose(csv);
}
 int buscarVendaPorId(unsigned int id){
    int i;
    VENDA venda;

    int encontrou = 0;

    for (i = 1; i <= quantidadeVendasCSV() && encontrou == 0; i++) // vai varrendo todas as linhas do arquivo csv ate achar algum que combina com o id
    {
        venda = retornarVendaNaLinha(i);
        if (venda.id == id) {
            encontrou = 1;
            printf("indice: %d\n",i);
            return i;
            //retorna a linha do venda no arquivo csv
        }
    }

    printf("nao existem vendas com esse id\n");
    return 0;
}
void modificarVendas(VENDA venda){
    char nomeArquivo[] = "Vendas.csv";
    FILE *csv, *temp;
    csv = fopen(nomeArquivo, "r");
    temp = fopen("temp.csv", "w"); // arquivo temporario
    int indice = buscarVendaPorId(venda.id);
    char linha[1000];
    int contador = 0;

    fgets(linha, sizeof(linha), csv);
    fprintf(temp, "%s", linha); // pega a linha do cabeçalho do arquivo original e joga no arquivo temporario
    printf("entrou\n");
    while (fgets(linha, sizeof(linha), csv) != NULL)
    { //os novos dados do produto sao jogados no arquivo temporario
        if (contador == indice - 1 )
        {
            printf("entrou\n");
            fprintf(temp, "%d;%s;%02d/%02d/%04d;%.2f;%d\n", venda.id, venda.CPF,  venda.data.dia, venda.data.mes, venda.data.ano,venda.valorTotal, venda.quantidade);
            printf("%d;%s;%02d/%02d/%04d;%.2f;%d\n", venda.id, venda.CPF,  venda.data.dia, venda.data.mes, venda.data.ano,venda.valorTotal, venda.quantidade);
        }
        else
        {
            fprintf(temp, "%s", linha);
        }
        contador = contador + 1;
    }
    printf("contador: %d",contador);
    fclose(csv);
    fclose(temp);

    remove(nomeArquivo);
    rename("temp.csv", nomeArquivo);// arquivo original é substituído pelo temporário
}
void buscaVendas(){
    int escolhaMenu;
    char cpf[15];
    char nome[51];
    CLIENTE cliente;
    int indiceCliente;

    printf("buscar vendas de qual cliente? pesquisar por:\n1. CPF\n2. Nome\n");
    scanf("%d", &escolhaMenu);
    if (escolhaMenu == 1)
    {
        printf("digite o CPF: ");
        scanf("%s", cpf);
    } else if (escolhaMenu == 2)
    {
        printf("digite o nome: ");
        scanf("%s", nome);
        indiceCliente = buscarClientePorNome(nome);
        cliente = retornarClienteNaLinha(indiceCliente);
        strcpy(cpf, cliente.CPF);
        printf("%s",cpf);
    }
    VENDA venda;
    char nomeArquivo[] = "Vendas.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r");

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), csv);  //faz pular o cabecalho

    int indiceAtual = 1;

    //vai passando de linha em linha ate chegar na linha que interessa, ai retorna um valor de tipo PRODUTO
    while (7 == fscanf(csv, "%d;%[^;];%d/%d/%d;%f;%d\n", &venda.id, venda.CPF, &venda.data.dia,
                       &venda.data.mes, &venda.data.ano, &venda.valorTotal, &venda.quantidade))
    {
        if (strcmp(cpf,venda.CPF)==0)
        {
            printf("%d/%d/%d: %.02f, %d produto(s)\n"
                   ,venda.data.dia,venda.data.mes,venda.data.ano,venda.valorTotal,venda.quantidade);
        }
        indiceAtual = indiceAtual + 1;

    }

    exit(1);
}

