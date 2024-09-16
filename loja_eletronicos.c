#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// define tamanho das constantes
#define MAX_USUARIOS 10
#define TAMANHO_NOME 30
#define TAMANHO_SENHA 5
#define LINHAS 5
#define COLUNAS 3
#define TAMANHO_ID 7
#define TAMANHO_STATUS 20
//

const char SENHA_CADASTRO[] = "2025";
// produto
typedef struct
{
    char id[TAMANHO_ID];
    char nome[TAMANHO_NOME];
    char status[TAMANHO_STATUS];
} Produto;

// usuario
typedef struct
{
    char nome[TAMANHO_NOME];
    char cargo[TAMANHO_NOME];
    char senha[TAMANHO_SENHA];
} Usuario;

// cria um array para armazena os produtos
Produto produtos[LINHAS][COLUNAS];
int quantidadeProdutos = 0;

// cria um array para armazena os usuarios
Usuario usuarios[MAX_USUARIOS];
int quantidadeUsuarios = 0;

/**
 * @brief funcao para cadastar um novo usuario
 * */
void cadastrarUsuario()
{
    // senha de cadastro
    char senha[TAMANHO_SENHA];

    int opcao = 0;
    do
    {
        printf("\nDigite a senha de cadastro: ");
        scanf("%s", senha);
        getchar();

        // verifica se a senha esta incorreta
        if (strcmp(senha, SENHA_CADASTRO) != 0)
        {

            printf("Senha incorreta!\n");
            printf("1 - Tenta novamente\n");
            printf("2 - Retorna ao menu anterior\n");
            printf("3 - Sair\n");
            printf("Porfavor, selecione uma das opcoes acima: ");
            scanf("%d", &opcao);
            system("cls || clear");
            getchar();

            switch (opcao)
            {
            case 1:
                continue; // Recomecao loop
                break;
            case 2:
                return; // retorna ao meno anterior
                break;
            case 3:
                printf("Saindo do Sistema");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                exit(1); // sai do programa
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }
        }
    } while (strcmp(senha, SENHA_CADASTRO) != 0);

    // verifica se a quantidade de usuarios excedeu o limite estabelecido.
    if (quantidadeUsuarios >= MAX_USUARIOS)
    {
        printf("Limite maximo de usuarios atingido!\n");
        return;
    }

    // recebe o nome do usuario
    printf("Digite o nome do usuario: ");
    scanf("%s", usuarios[quantidadeUsuarios].nome);

    printf("Digite o cargo do usuario (Admin ou Vendedor): "); // recebe o cargo do usuario
    scanf("%s", usuarios[quantidadeUsuarios].cargo);
    getchar();
    // verifica se o cargo digitado eh invalido
    if (strcmp(usuarios[quantidadeUsuarios].cargo, "Admin") != 0 && strcmp(usuarios[quantidadeUsuarios].cargo, "Vendedor") != 0)
    {
        printf("Cargo Invalido. Digite 'Admin' ou 'Vendedor' ");
        return cadastrarUsuario();
    }
    printf("Digite a senha (maximo 4 digitos): "); // recebe a senha do usuario
    scanf("%4s", usuarios[quantidadeUsuarios].senha);
    getchar();
    // limpa a tela
    system("cls || clear");
    quantidadeUsuarios++; // incrementa a variavel em 1
    printf("Usuario cadastrado com sucesso!\n");
    printf("Pressione 'enter' para continuar");
    getchar();
    // limpa a tela
    system("cls || clear");
}

/**
 * @brief funcao retorna uma lista com todos os produtos
 * */
void relatorioProduto()
{
    int contador = 1;

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (strlen(produtos[i][j].id) > 0)
            {
                printf("\n\nProduto %d:\n", contador);
                printf("ID: %s\n", produtos[i][j].id);
                printf("Nome: %s\n", produtos[i][j].nome);
                printf("Status: %s\n", produtos[i][j].status);
                printf("\n");
                contador++;
            }
        }
    }
    if (contador == 1)
    {
        printf("Nenhum produto cadastrado.\n");
    }
}
void cadastrarProduto()
{
    if (quantidadeProdutos >= LINHAS * COLUNAS)
    {
        printf("Limite máximo de produtos atingido!\n");
        return;
    }

    int linha = quantidadeProdutos / COLUNAS;
    int coluna = quantidadeProdutos % COLUNAS;
    while (1)
    {
        char id_digitado[100];
        printf("Digite o ID do produto (6 digitos): ");
        fgets(id_digitado, sizeof(id_digitado), stdin);
        id_digitado[strcspn(id_digitado, "\n")] = 0; // ignora o "/n";

        if (strlen(id_digitado) != 6)
        {
            printf("ID invalido!Digite um ID com 6 digitos. Pressione Enter para continuar...");
            getchar();
            system("cls || clear");
            continue; // volta ao inicio do loop para solicitar a entrada novamente
        }
        else
        {
            // copia o id digitado para o array de produtos
            strcpy(produtos[linha][coluna].id, id_digitado);
            break; // interrompe o loop
        }
    }

    printf("Digite o nome do produto: ");
    fgets(produtos[linha][coluna].nome, TAMANHO_NOME, stdin);
    produtos[linha][coluna].nome[strcspn(produtos[linha][coluna].nome, "\n")] = 0; // Remover o '\n' do final


    printf("Digite o status do produto: ");
    fgets(produtos[linha][coluna].status, TAMANHO_STATUS, stdin);
    produtos[linha][coluna].status[strcspn(produtos[linha][coluna].status, "\n")] = 0; // Remover o '\n' do final

    quantidadeProdutos++;
    printf("\nProduto cadastrado com sucesso!\n");
    printf("Pressione 'enter' para continuar \n");
    getchar();
    system("cls || clear");
    
}
void excluirProduto()
{
    char id_excluir[TAMANHO_ID];
    printf("Digite o ID do produto que deseja excluir: ");
    scanf("%s", id_excluir);
    getchar();

    int encontrar_id = 0;
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (strcmp(produtos[i][j].id, id_excluir) == 0)
            {
                printf("Excluindo produto");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                encontrar_id = 1;
                produtos[i][j].id[0] = '\0';
                produtos[i][j].nome[0] = '\0';
                produtos[i][j].status[0] = '\0';
                quantidadeProdutos--;
                printf("Produto excluído!\n");
                system("cls || clear");
            }
        }
    }
    if (!encontrar_id)
    {
        printf("Produto não encontrado no sistema!\n\n");
        excluirProduto();
    }
}
void atualizarProduto()
{
    char id_atualizar[TAMANHO_ID];
    printf("Digite o ID do produto que deseja atualizar: ");
    scanf("%s", id_atualizar);
    getchar();

    int encontrar_id = 0;
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (strcmp(produtos[i][j].id, id_atualizar) == 0)
            {
                printf("Procurando produto");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\nProduto encontrado");
                encontrar_id = 1;
                while (1)
                {
                    char id_digitado[100];
                    printf("\nDigite o novo ID do produto (6 digitos): ");
                    fgets(id_digitado, sizeof(id_digitado), stdin);
                    id_digitado[strcspn(id_digitado, "\n")] = 0;

                    if (strlen(id_digitado) != 6)
                    {
                        printf("ID invalido!Digite um ID com 6 digitos. Pressione Enter para continuar...");
                        getchar();
                        system("cls || clear");
                        continue; // volta ao inicio do loop para solicitar a entrada novamente
                    }
                    else
                    {
                        // copia o id digitado para o array de produtos
                        strcpy(produtos[i][j].id, id_digitado);
                        break; // interrompe o loop
                    }
                }

                printf("Digite o novo nome do produto: ");
                scanf("%s", produtos[i][j].nome);
                getchar(); // Limpar o buffer de entrada

                printf("Digite o novo status do produto: ");
                fgets(produtos[i][j].status, TAMANHO_STATUS, stdin);
                produtos[i][j].status[strcspn(produtos[i][j].status, "\n")] = 0; // Remover o '\n' do final
                system("cls || clear");
            }
        }
    }
    if (!encontrar_id)
    {
        printf("Produto não encontrado no sistema!\n\n");
        atualizarProduto();
    }
}

void consultaId()
{
    char id_consulta[TAMANHO_ID];
    printf("Digite o ID para consulta de produto: ");
    scanf("%s", id_consulta);
    getchar();

    int encontrar_id = 0;
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (strcmp(produtos[i][j].id, id_consulta) == 0)
            {
                printf("Procurando produto");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\nProduto encontrado\n");
                printf("ID: %s\n", produtos[i][j].id);
                printf("Nome: %s\n", produtos[i][j].nome);
                printf("Status: %s\n", produtos[i][j].status);
                printf("\n");
                encontrar_id = 1;
                printf("Produto encontrado com sucesso!\n");
                printf("Pressione 'enter' para continuar ");
                getchar();
                system("cls || clear");
                break;
            }
        }
    }
    if (!encontrar_id)
    {
        printf("Produto não encontrado no sistema!\n\n");
        consultaId();
    }
}

void Sistema()
{
    char nome[TAMANHO_NOME];
    char senha[TAMANHO_SENHA];
    int opcao;
    char cargo[TAMANHO_NOME];
    do
    {
        system("cls || clear");
        // recebe o nome do usuario já criado no sistema
        printf("Digite o nome do usuario: ");
        scanf("%s", nome);
        getchar();

        // recebe a senha do usuario já criado no sistema
        printf("Digite a senha do usuario: ");
        scanf("%s", senha);
        getchar();
        system("cls || clear");

        // verifico se o nome e senha do usuario são válidos
        int usuarioEncontrado = 0;
        for (int i = 0; i < quantidadeUsuarios; i++)
        {
            // uso strcmp para fazer a comparação do nome e senha digitado pelo usuario com os contidos no sistema
            if (strcmp(nome, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0)
            {
                strcpy(cargo, usuarios[i].cargo);
                printf("Bem vindo ao sistema da MDM Eletronica\n");
                printf("Usuario: %s.\n", usuarios[i].nome);
                printf("Cargo: %s.\n\n", usuarios[i].cargo);
                usuarioEncontrado = 1;
                do
                {
                    if (strcmp(cargo, "Admin") == 0)
                    {
                        printf("1.Cadastro Produto\n");
                        printf("2.Consultar Produto\n");
                        printf("3.Excluir Produto\n");
                        printf("4.Atualizar Produto\n");
                        printf("5.Sair\n");
                        printf("Escolha uma opcao: ");
                    }
                    else if (strcmp(cargo, "Vendedor") == 0)
                    {
                        printf("1.Consultar Produto\n");
                        printf("2.Relatorio dos Produtos\n");
                        printf("3.Sair\n");
                        printf("Escolha uma opcao: ");
                    }
                    scanf("%d", &opcao);
                    getchar();

                    if (strcmp(cargo, "Admin") == 0)
                    {
                        switch (opcao)
                        {
                        case 1:
                            cadastrarProduto();
                            break;
                        case 2:
                            consultaId();
                            break;
                        case 3:
                            excluirProduto();
                            break;
                        case 4:
                            atualizarProduto();
                            break;
                        case 5:
                            printf("Saindo do Usuario Admin");
                            for (int i = 0; i < 3; i++)
                            {
                                printf(".");
                                fflush(stdout);
                                sleep(1);
                            }
                            system("cls || clear");
                            break;
                        default:
                            printf("Digite uma opção valida.\n");
                        }
                    }
                    else if (strcmp(cargo, "Vendedor") == 0)
                    {
                        switch (opcao)
                        {
                        case 1:
                            consultaId();
                            break;
                        case 2:
                            relatorioProduto();
                            break;
                        case 3:
                            printf("Saindo do Usuario Vendedor");
                            for (int i = 0; i < 3; i++)
                            {
                                printf(".");
                                fflush(stdout);
                                sleep(1);
                            }
                            system("cls || clear");
                            break;
                        default:
                            printf("Digite uma opção valida.\n");
                        }
                    }
                } while ((strcmp(cargo, "Admin") == 0 && opcao != 5) || (strcmp(cargo, "Vendedor") == 0 && opcao != 3));

                return;
            }
        }
        // caso o usuario nao tenha sido encontrado
        if (!usuarioEncontrado)
        {

            printf("Usuario ou senha incorretos\n");
            printf("1 - Tentar Novamente\n");
            printf("2 - voltar ao Menu anterior\n");
            printf("3 - sair\n");
            printf("Selecione uma das opcoes acima: ");
            scanf("%d", &opcao);
            getchar();

            switch (opcao)
            {
            case 1:
                continue; // volta para o inicio do loop
                break;

            case 2:
                main(); // retorna ao menu anterior
                break;
            case 3:
                printf("Saindo do Sistema");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                exit(1); // encerra a execucao do programa

            default:
                printf("Porfavor, selecione uma opcao valida\n");
                break;
            }
        }

    } while (1);
}

// funcao principal
int main()
{
    int opcao;

    do
    {

        printf("\n----------------------------------\n");
        printf("MDM Eletronica - Tela inicial\n");
        printf("1. Cadastro de Usuario\n");
        printf("2. Entrar no Sistema\n");
        printf("3. Sair\n");
        printf("\n----------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        system("cls || clear");

        switch (opcao)
        {
        case 1:
            cadastrarUsuario();
            break;
        case 2:
            Sistema();
            break;
        case 3:
            printf("Saindo do Sistema");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                fflush(stdout);
                sleep(1);
            }
            exit(1); // encerrar o programa
            break;
        default:
            printf("Porfavor, selecione uma opcao valida\n");
            printf("Pressione enter para continuar\n");
            getchar();
            system("cls || clear");
            break;
        }

    } while (opcao != 3);

    return 0;
}
