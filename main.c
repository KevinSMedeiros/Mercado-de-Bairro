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
    int opcao;
    CLIENTE novoCliente;
    PRODUTO novoProduto;
    char cpf[15];
    char nome[51];

    //o programa inteiro ta dividido nesse grande switch que serve como menu:

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
                break;
            }

        break;

        case 2:
            printf("\n###### MENU DE CLIENTES ######\n\n1. cadastrar novo cliente\n2. modificar dados de cliente\n3. verificar o numero de clientes entre 18 e 25 anos\n4. listar clientes acima de 1000 pontos\n\n9. Sair\n");
            scanf("%d", &escolhaMenu);

            switch (escolhaMenu)
            {
                case 1:

                    printf("digite os dados do cliente pra cadastrar:\n");

                    printf("\nCPF: ");
                    scanf("%s", novoCliente.CPF);

                    //fgets permite que as strings possuam espacos
                    //a funcao strcspn acha a quebra de linha e remove ela. se nao usar isso, cada informacao fica em uma linha diferente

                    printf("nome: ");
                    scanf(" ");
                    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
                    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

                    printf("data de nascimento (digite no formato 'DD MM AAAA'): ");
                    scanf("%d %d %d", &novoCliente.dataNascimento.dia, &novoCliente.dataNascimento.mes, &novoCliente.dataNascimento.ano);

                    printf("idade: ");
                    scanf("%d", &novoCliente.idade);

                    printf("endereco: ");
                    scanf(" ");
                    fgets(novoCliente.endereco, sizeof(novoCliente.endereco), stdin);
                    novoCliente.endereco[strcspn(novoCliente.endereco, "\n")] = '\0'; // Remove a quebra de linha

                    printf("cidade: ");
                    fgets(novoCliente.cidade, sizeof(novoCliente.cidade), stdin);
                    novoCliente.cidade[strcspn(novoCliente.cidade, "\n")] = '\0'; // Remove a quebra de linha

                    printf("estado (sigla de 2 letras: ");
                    fgets(novoCliente.estado, sizeof(novoCliente.estado), stdin);
                    novoCliente.estado[strcspn(novoCliente.estado, "\n")] = '\0'; // Remove a quebra de linha

                    printf("pontos: ");
                    scanf("%d", &novoCliente.pontos);

                    cadastrarCliente(novoCliente); // essa funcao pega tudo o que o usuario digitou no "novoCliente" como parâmetro joga pro arquivo csv

                    printf("\no cliente foi cadastrado.\n");

                    printf("\ndados do novo cliente:\n");
                    exibirCliente(novoCliente);
                break;

                case 2:
                    modificarCliente();
                break;

                case 3:
                    printf("tem %d clientes entre 18 e 25", quantosClientesEntre18e25());
                break;

                case 4:
                    mostrarNomesComMaisDeMilPontos();
                break;

                case 9:
                    printf("\nprograma finalizado.\n");
                break;
            }
        break;

        case 3:
            printf("\n###### MENU DE PRODUTOS ######\n\n1. Cadastrar novo produto\n2. Atualizar informações do produto\n3. listar produtos por setor\n4. estoque de cada setor\n5. Produtos com estoque baixo\n\n9. Sair\n");
            scanf("%d", &escolhaMenu);

            switch (escolhaMenu)
            {
                case 1:
                    novoProduto.id = obterProximoIdProduto(); // essa funcao olha qual é o id do ultimo produto registrado. o proximo vai ser 1 a mais

                    printf("digite os dados do produto pra adicionar\n");

                    printf("\nsetor:\n1. Higiene\n2. Limpeza\n3. Bebidas\n4. Frios\n5. Padaria\n6. Acougue\n");
                    // para o professor: o valor numerico foi pra facilitar a entrada, na struct os setores continuam como strings.
                    scanf("%d",&opcao);
                    switch (opcao) //nao da pra atribuir um valor direto na string, por isso o strcpy
                    {
                        case 1:
                            strcpy(novoProduto.setor, "Higiene");
                        break;

                        case 2:
                            strcpy(novoProduto.setor, "Limpeza");
                        break;

                        case 3:
                            strcpy(novoProduto.setor, "Bebidas");
                        break;

                        case 4:
                            strcpy(novoProduto.setor, "Frios");
                        break;

                        case 5:
                            strcpy(novoProduto.setor, "Padaria");
                        break;

                        case 6:
                            strcpy(novoProduto.setor, "Açougue");
                        break;
                    }

                    //fgets permite que a string nome possua espacos
                    //a funcao strcspn acha a quebra de linha e remove ela. se nao usar isso, cada informacao fica em uma linha diferente

                    printf("nome: ");
                    scanf(" ");
                    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
                    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

                    printf("preco: R$");
                    scanf("%f", &novoProduto.preco);

                    printf("data de validade (digite no formato 'DD MM AAAA'): ");
                    scanf("%d %d %d", &novoProduto.dataValidade.dia, &novoProduto.dataValidade.mes, &novoProduto.dataValidade.ano);

                    printf("estoque: ");
                    scanf("%d", &novoProduto.estoque);

                    gravarProdutoCSV(novoProduto);
                    // igual acontece pros clientes, essa funcao pega tudo oq o usuario digitou em novoProduto como parâmetro e joga no arquivo csv

                    printf("\no produto foi adicionado.\n");
                break;

                case 2:
                    modificarProduto();
                break;

                case 3:
                    listarProdutosPorSetor();
                break;

                case 4:
                    calcularEstoqueDeCadaSetor();
                break;

                case 5:
                    mostrarProdutosComEstoqueAbaixoDe5();
                break;

                case 9:
                    printf("\nprograma finalizado.\n");
                break;
            }
        break;

        case 9:
            printf("\nPrograma finalizado.\n");
        break;
    }

return 0;
}
