#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cliente.h"

void cadastrarCliente(CLIENTE c)
{
    char nomeArquivo[] = "Clientes.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "a"); // modo "a" de append, pq vai adicionar arquivos no final do texto, nao sobrescrever

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
void interfaceCadastrarCliente(CLIENTE novoCliente){
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
}

void modificarCliente()
{
    int escolhaMenu;
    char cpf[15];
    char nome[51];
    CLIENTE cliente;
    int indiceCliente;

    printf("qual cliente atualizar? pesquisa por:\n1. CPF\n2. Nome\n");
    scanf("%d", &escolhaMenu);
    if (escolhaMenu == 1)
    {
        printf("digite o CPF: ");
        scanf("%s", cpf);
        indiceCliente = buscarClientePorCPF(cpf);
    } else if (escolhaMenu == 2)
    {
        printf("digite o nome: ");
        scanf("%s", nome);
        indiceCliente = buscarClientePorNome(nome);
    }
    // as funções de buscar cliente por cpf e nome retornam o indice do cliente no arquivo csv
    // isso é util pq com a informação do indíce vc pode acessar facilmente o mesmo cliente denovo no arquivo

    printf("\ndetalhes do cliente:\n");
    exibirCliente(retornarClienteNaLinha(indiceCliente));
    cliente = retornarClienteNaLinha(indiceCliente);
    //salva as informacoes do cliente encontrado numa variavel local

    printf("\nescolha a informacao pra modificar:\n");
    printf("1. nome\n");
    printf("2. data de nascimento\n");
    printf("3. idade\n");
    printf("4. endereco\n");
    printf("5. cidade\n");
    printf("6. estado\n");
    printf("7. pontos\n");
    printf("9. sair\n");

    int opcao;
    scanf("%d", &opcao);

    switch (opcao)
    {
        case 1:
            printf("novo nome: ");
            scanf("%s", cliente.nome);
        break;

        case 2:
            printf("nova data de nascimento (use o formato 'DD MM AAAA'): ");
            scanf("%d %d %d", &cliente.dataNascimento.dia, &cliente.dataNascimento.mes, &cliente.dataNascimento.ano);
        break;

        case 3:
            printf("nova idade: ");
            scanf("%d", &cliente.idade);
        break;

        case 4:
            printf("novo endereço: ");
            scanf("%s", cliente.endereco);
        break;

        case 5:
            printf("nova cidade: ");
            scanf("%s", cliente.cidade);
        break;

        case 6:
            printf("novo estado: ");
            scanf("%s", cliente.estado);
        break;

        case 7:
            printf("pontuacao nova: ");
            scanf("%d", &cliente.pontos);
        break;

        case 9:
        break;
    }

    char nomeArquivo[] = "Clientes.csv";
    FILE *csv, *temp;
    csv = fopen(nomeArquivo, "r");
    temp = fopen("temp.csv", "w"); //arquivo temporario

    char linha[1000];
    int contador = 0;

    fgets(linha, sizeof(linha), csv);
    fprintf(temp, "%s", linha); // pega a linha do cabeçalho do arquivo original e joga no arquivo temporario

    while (fgets(linha, sizeof(linha), csv) != NULL)
    { //os novos dados do cliente sao jogados no arquivo temporario
        if (contador == indiceCliente - 1)// -1 porque o indice comeca direto no 1, nao no 0
        {
            fprintf(temp, "%s;%s;%02d/%02d/%04d;%d;%s;%s;%s;%d\n", cliente.CPF, cliente.nome, cliente.dataNascimento.dia, cliente.dataNascimento.mes, cliente.dataNascimento.ano, cliente.idade, cliente.endereco, cliente.cidade, cliente.estado, cliente.pontos);
        }
        else
        {
            fprintf(temp, "%s", linha);
        }
        contador++;
    }

    fclose(csv);
    fclose(temp);

    remove(nomeArquivo);
    rename("temp.csv", nomeArquivo); // arquivo original é substituído pelo temporário

    printf("cliente atualizado.\n");
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

    //vai passando de linha em linha ate chegar na linha que interessa, ai retorna um valor de tipo CLIENTE
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

int buscarClientePorCPF(char cpf[15])
{
    int i;
    CLIENTE cliente;

    int encontrou = 0;

    for(i = 1; i <= quantidadeClientesCSV(); i++)
    {
        cliente = retornarClienteNaLinha(i); // vai varrendo todas as linhas do arquivo csv ate achar algum que combina com o cpf
        if(strcmp(cliente.CPF, cpf) == 0) //strcmp serve pra comparar string, o valor 0 significa que sao iguais
        {
            printf("\n%s", cliente.nome);
            encontrou = 1;
            return i;
            //retorna o indice do cliente do arquivo
        }
    }
        printf("nao tem cliente com esse cpf");
        return 0;

}

int buscarClientePorNome(char nome[51])
{
    int i;
    CLIENTE cliente;

    int encontrou = 0;

    for(i = 1; i <= quantidadeClientesCSV() && encontrou == 0; i++)
    {
        cliente = retornarClienteNaLinha(i);  // vai varrendo todas as linhas do arquivo csv ate achar algum que combina com o nome
        if(strcmp(cliente.nome, nome) == 0)  //strcmp serve pra comparar string, o valor 0 significa que sao iguais
        {
            printf("\n%s", cliente.nome);
            encontrou = 1;
            return i;
            ///retorna a linha do cliente do arquivo
        }
    }
    if(encontrou == 0)
    {
        printf("nao tem clientes com esse nome");
        return 0;
    }
}

void mostrarNomesComMaisDeMilPontos()
{
    int i;
    CLIENTE cliente;

    printf("\n### CLIENTES COM MAIS DE 1000 PONTOS ###\n");

    for(i = 1; i <= quantidadeClientesCSV(); i++)
    {
        cliente = retornarClienteNaLinha(i); // vai varrendo todas as linhas do arquivo csv
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
        cliente = retornarClienteNaLinha(i); // vai varrendo todas as linhas do arquivo csv
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
