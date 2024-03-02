#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "produtos.h"
#include "tempo.h"
#include "cliente.h"
#include "vendas.h"
#include "itensCompra.h"

int main()
{

    int escolhaMenu;

    printf("\n###### MENU DO MERCADINHO ######\n\n1. Venda\n2. Clientes\n3. Produtos\n\n9. Sair\n");
    scanf("%d", &escolhaMenu);
    switch (escolhaMenu)
    {
        case 1:
            printf("\n###### MENU DE VENDAS ######\n\n1. Nova venda\n2. Listar venda do clientes\n\n9. Sair\n");
            scanf("%d", &escolhaMenu);

            switch (escolhaMenu)
            {
                case 1:

                break;

                case 2:

                break;

                case 9:
                    printf("\nprograma finalizado.\n");
                    //return 0;
                break;
            }

        break;

        case 2:
            printf("\n###### MENU DE CLIENTES ######\n\n1. Cadastrar novo cliente\n2. atualizar pontuação\n3. Atualizar cliente\n4. Listar clientes entre 18 e 25\n5. Listar clientes acima de 1000 pontos\n\n9. Sair\n");
            scanf("%d", &escolhaMenu);

            switch (escolhaMenu)
            {
                case 1:

                break;

                case 2:

                break;

                case 3:

                break;

                case 4:

                break;

                case 5:

                break;

                case 9:
                    printf("\nprograma finalizado.\n");
                    //return 0;
                break;
            }
        break;

        case 3:
            printf("\n###### MENU DE PRODUTOS ######\n\n1. Cadastrar novo produto\n2. Atualizar informações do produto\n3. Estoque por setor\n4. Produtos com estoque baixo\n\n9. Sair\n");
            scanf("%d", &escolhaMenu);

            switch (escolhaMenu)
            {
                case 1:
                    PRODUTO novoProduto;

                    novoProduto.id = obterProximoIdProduto();

                    printf("digite os dados do produto que deseja adicionar:\n");
                    printf("setor: ");
                    scanf("%s", novoProduto.setor);
                    printf("nome: ");
                    scanf("%s", novoProduto.nome);
                    printf("preco: ");
                    scanf("%f", &novoProduto.preco);
                    printf("data de validade (digite no formato 'DD MM AAAA'): ");
                    scanf("%d %d %d", &novoProduto.dataValidade.dia, &novoProduto.dataValidade.mes, &novoProduto.dataValidade.ano);
                    printf("estoque: ");
                    scanf("%d", &novoProduto.estoque);

                    gravarProdutoCSV(novoProduto);

                    printf("\no produto foi adicionado.\n");
                break;

                case 2:

                break;

                case 3:

                break;

                case 9:
                    printf("\nprograma finalizado.\n");
                    //return 0;
                break;
            }
        break;

        case 9:
            printf("\nPrograma finalizado.\n");
            //return 0;
        break;
    }

return 0;
}
