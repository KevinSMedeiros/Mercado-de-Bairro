#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "produtos.h"


unsigned int obterProximoIdProduto()
{
    FILE *arquivo;
    arquivo = fopen("Produtos.csv", "r");

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

void gravarProdutoCSV(PRODUTO p)
{
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "a"); // modo append pq vai adicionar text no final, sem sobrescrever

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

void interfaceModificarProduto()
{
    int escolhaMenu;
    char nome[51];
    PRODUTO produto;
    int indiceProduto;

    printf("qual produto atualizar? pesquisa por:\n1. ID\n2. Nome\n");
    scanf("%d", &escolhaMenu);
    if (escolhaMenu == 1)
    {
        printf("digite o ID: ");
        scanf("%d", &indiceProduto);
    }
    else if (escolhaMenu == 2)
    {
        printf("digite o nome: ");
        scanf("%s", nome);
        indiceProduto = buscarProdutoPorNome(nome);
    }

    // igual nos clientes, as funções de buscar produto por id e nome retornam o id do produto no arquivo csv
    // isso é util pq com a informação do indíce vc pode acessar facilmente o mesmo produto denovo no arquivo

    printf("detalhes do produto:\n");
    exibirProduto(retornarProdutoNaLinha(indiceProduto));
    produto = retornarProdutoNaLinha(indiceProduto);
    //salva as informacoes do produto encontrado numa variavel local

    printf("\no que voce quer modificar?:\n");
    printf("1. setor\n");
    printf("2. nome\n");
    printf("3. preço\n");
    printf("4. data de validade\n");
    printf("5. estoque\n");

    int opcao; // opcao de campo pra alterar
    int opcao2; // opcao de setor, caso setor seja escolhido pra ser modificado

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
        case 1:
            printf("\nnovo setor:\n1. Higiene\n2. Limpeza\n3. Bebidas\n4. Frios\n5. Padaria\n6. Acougue\n");
            // para o professor: o valor numerico foi pra facilitar a entrada, na struct os setores continuam como strings.
            scanf("%d",&opcao2);
            switch (opcao2) //nao da pra atribuir um valor direto na string, por isso o strcpy
            {
                case 1:
                    strcpy(produto.setor, "Higiene");
                break;

                case 2:
                    strcpy(produto.setor, "Limpeza");
                break;

                case 3:
                    strcpy(produto.setor, "Bebidas");
                break;

                case 4:
                    strcpy(produto.setor, "Frios");
                break;

                case 5:
                    strcpy(produto.setor, "Padaria");
                break;

                case 6:
                    strcpy(produto.setor, "Açougue");
                break;
            }
            break;

        case 2:
            printf("novo nome: ");
            scanf(" ");
            fgets(produto.nome, sizeof(produto.nome), stdin);
            produto.nome[strcspn(produto.nome, "\n")] = '\0';
            //fgets permite que a string nome possua espacos
            //a funcao strcspn acha a quebra de linha e remove ela. se nao usar isso, cada informacao fica em uma linha diferente
            break;

        case 3:
            printf("novo preco: R$");
            scanf("%f", &produto.preco);
            break;

        case 4:
            printf("nova data de validade (use o formato 'DD MM AAAA'): ");
            scanf("%d %d %d", &produto.dataValidade.dia, &produto.dataValidade.mes, &produto.dataValidade.ano);
            break;

        case 5:
            printf("novo estoque: ");
            scanf("%d", &produto.estoque);
            break;
    }
    modificarProduto(produto,indiceProduto);
    printf("produto modificado\n");
}
void modificarProduto(PRODUTO produto, int indice){
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv, *temp;
    csv = fopen(nomeArquivo, "r");
    temp = fopen("temp.csv", "w"); // arquivo temporario

    char linha[1000];
    int contador = 0;

    fgets(linha, sizeof(linha), csv);
    fprintf(temp, "%s", linha); // pega a linha do cabeçalho do arquivo original e joga no arquivo temporario

    while (fgets(linha, sizeof(linha), csv) != NULL)
    { //os novos dados do produto sao jogados no arquivo temporario
        if (contador == indice - 1) // -1 porque o indice comeca direto no 1, nao no 0
        {
            fprintf(temp, "%d;%s;%s;%.2f;%02d/%02d/%04d;%d\n", produto.id, produto.setor, produto.nome, produto.preco, produto.dataValidade.dia, produto.dataValidade.mes, produto.dataValidade.ano, produto.estoque);
        }
        else
        {
            fprintf(temp, "%s", linha);
        }
        contador = contador + 1;
    }

    fclose(csv);
    fclose(temp);

    remove(nomeArquivo);
    rename("temp.csv", nomeArquivo);// arquivo original é substituído pelo temporário
}
void exibirProduto(PRODUTO p)
{
    printf("\n######################################\n");
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
    printf("\n######################################\n");
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

    //vai passando de linha em linha ate chegar na linha que interessa, ai retorna um valor de tipo PRODUTO
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

int buscarProdutoPorID(int id) {
    int i;
    PRODUTO produto;

    int encontrou = 0;

    for (i = 1; i <= quantidadeProdutosCSV() && encontrou == 0; i++) // vai varrendo todas as linhas do arquivo csv ate achar algum que combina com o id
    {
        produto = retornarProdutoNaLinha(i);
        if (produto.id == id) {
            printf("%s\n",produto.nome);
            encontrou = 1;
            return i;
            //retorna a linha do produto no arquivo csv
        }
    }

        printf("nao existem produtos com esse id\n");
        return 0;

}

int buscarProdutoPorNome(char nome[51])
{
    int i;
    PRODUTO produto;

    int encontrou = 0;

    for(i = 1; i <= quantidadeProdutosCSV() && encontrou == 0; i++) // vai varrendo todas as linhas do arquivo csv ate achar algum que combina com o nome
    {
        produto = retornarProdutoNaLinha(i);
        if(strcmp(produto.nome, nome) == 0) //strcmp serve pra comparar string, o valor 0 significa que sao iguais
        {
            encontrou = 1;
            return i;
            //retorna a linha do produto no arquivo csv
        }
    }
    if(encontrou == 0)
    {
        printf("esse produto nao existe");
    }
}

void mostrarProdutosComEstoqueAbaixoDe5()
{
    int i;
    PRODUTO produto;

    printf("\n### PRODUTOS COM ESTOQUE ABAIXO DE 5 ###\n");

    for(i = 1; i <= quantidadeProdutosCSV(); i++) // varre todas as linhas do arquivo csv
    {
        produto = retornarProdutoNaLinha(i);
        if(produto.estoque < 5)
        {
            printf("\n%s, %d restantes", produto.nome, produto.estoque);
        }
    }
    printf("\n###################################\n");
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

void listarProdutosPorSetor()
{
    int i;
    int opcao;
    char setorSelecionado[11];
    PRODUTO produto;

    printf("\nvoce quer uma lista dos produtos de qual setor? \n1. Higiene\n2. Limpeza\n3. Bebidas\n4. Frios\n5. Padaria\n6. Acougue\n");
    // para o professor: o valor numerico foi pra facilitar a entrada, na struct os setores continuam como strings
    scanf("%d",&opcao);
    switch (opcao) //nao da pra atribuir um valor direto na string, por isso o strcpy
    {
        case 1:
            strcpy(setorSelecionado, "Higiene");
        break;

        case 2:
            strcpy(setorSelecionado, "Limpeza");
        break;

        case 3:
            strcpy(setorSelecionado, "Bebidas");
        break;

        case 4:
            strcpy(setorSelecionado, "Frios");
        break;

        case 5:
            strcpy(setorSelecionado, "Padaria");
        break;

        case 6:
            strcpy(setorSelecionado, "Açougue");
        break;
    }
    printf("\n##### LISTAGEM DE SETOR #####\n");

    for(i = 1; i <= quantidadeProdutosCSV(); i++) //passa por todas as linhas do arquivo
    {
        produto = retornarProdutoNaLinha(i);
        if(strcmp(produto.setor, setorSelecionado) == 0) //strcmp serve pra comparar strings, ai se ele retornar 0 significa que sao iguais
        {
            printf(("\n%s", produto.nome)); //printa o nome do produto se ele é do setor selecionado.
        }
    }
    printf("\n\n##############################\n");
}

void calcularEstoqueDeCadaSetor()
{
    int estoqueHigiene = 0;
    int estoqueLimpeza = 0;
    int estoqueFrios = 0;
    int estoqueAcougue = 0;
    int estoqueBebidas = 0;
    int estoquePadaria = 0;

    PRODUTO produto;
    int i;

    for(i = 1; i <= quantidadeProdutosCSV(); i++)
    //isso aqui é um loop que lê todas as linhas de produtos, e dependendo de qual
    //setor cada linha indicar, ele pega o valor de estoque e soma na categoria correspondente
    {
        produto = retornarProdutoNaLinha(i);
        if(strcmp(produto.setor, "Higiene") == 0)
        {
            estoqueHigiene = estoqueHigiene + produto.estoque;
        }
        else if(strcmp(produto.setor, "Limpeza") == 0)
        {
            estoqueLimpeza = estoqueLimpeza + produto.estoque;
        }
        else if(strcmp(produto.setor, "Bebidas") == 0)
        {
            estoqueBebidas = estoqueBebidas + produto.estoque;
        }
        else if(strcmp(produto.setor, "Padaria") == 0)
        {
            estoquePadaria = estoquePadaria + produto.estoque;
        }
        else if(strcmp(produto.setor, "Frios") == 0)
        {
            estoqueFrios = estoqueFrios + produto.estoque;
        }
        else if(strcmp(produto.setor, "Açougue") == 0)
        {
            estoqueAcougue = estoqueAcougue + produto.estoque;
        }
    } //strcmp serve pra comparar strings, ai se ele retornar 0 significa que sao iguais

    printf("\n### ESTOQUE DE CADA SETOR ###\n");

    printf("\nEstoque de Higiene: %d", estoqueHigiene);
    printf("\nEstoque de Limpeza: %d", estoqueLimpeza);
    printf("\nEstoque de Bebidas: %d", estoqueBebidas);
    printf("\nEstoque de Frios: %d", estoqueFrios);
    printf("\nEstoque de Padaria: %d", estoquePadaria);
    printf("\nEstoque de Açougue: %d", estoqueAcougue);

    printf("\n\n##############################\n");

}
