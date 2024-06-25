#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "funcoes.h"
#include "struct.h"
#include "assinaturas.h"

// Função para imprimir o menu principal
void imprimirMenu()
{
    printf("1. Gestao de usuarios\n");
    printf("2. Backoffice (necessita de autenticacao do adm)\n");
    printf("3. Aplicacao (necessita de autenticacao do usuario)\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para imprimir o menu de gestão de usuários
void gestaoUsuariosMenu()
{
    printf("\n \t\t\t\t\t\t\t Menu de Gestao de Usuarios \n");
    printf("1. Cadastrar novo usuario\n");
    printf("2. Remover usuario\n");
    printf("3. Imprimir lista de usuarios\n");
    printf("4. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");

    int opcao;
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        // Funcionalidade de cadastrar novo usuário
        printf("\n \t\t\t Cadastrar novo usuario \n");
        cadastrarUsuario();
        break;
    case 2:
        // Funcionalidade de remover usuário
        printf("\n \t\t\t Remover usuario \n");
        removerUsuario();
        break;
    case 3:
        // Funcionalidade de imprimir lista de usuários
        printf("\n \t\t\t Imprimir lista de usuarios \n");
        imprimirListaUsuarios();
        break;
    case 4:
        // Voltar ao menu principal
        printf("Voltando ........\n");
        break;
    default:
        printf("Opcao invalida.\n");
    }
}

// Função para imprimir o menu do backoffice
void backofficeMenu(Grafo *grafo, ListaUsuarioTaxi *listaUsuarioTaxi, ListaVertices *listaVertices)
{
    while (1)
    {
        printf("\n \t\t\t\t\t\t\t  Menu de Backoffice \n");
        printf("1. Adicionar nova rua\n");
        printf("2. Remover rua\n");
        printf("3. Adicionar buracos\n");
        printf("4. Remover buracos\n");
        printf("5. Imprimir localidade\n");
        printf("6. Imprimir todos os caminhos sem buracos\n");
        printf("7. Cadastrar taxistas\n");
        printf("8. Imprimir menu principal\n");
        printf("Escolha uma opcao: ");

        int opcao;
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            adicionarNovaRua(grafo);
            break;
        case 2:
            removerRua(grafo);
            break;
        case 3:
            adicionarBuracos(grafo);
            break;
        case 4:
            int peso;
            printf("Digite o peso original: ");
            scanf("%d", &peso);

            removerBuracos(grafo, peso); // Remover buracos com o peso original fornecido
            break;
        case 5:
            imprimirLocalidade(grafo);
            break;
        case 6:
            int inicio, destino;
            printf("Digite o vertice de inicio: ");
            scanf("%d", &inicio);

            printf("\nDigite o vertice de destino: ");
            scanf("%d", &destino);

            imprimirTodosCaminhosSemBuracos(grafo, inicio, destino); // Imprimir caminhos sem buracos
            break;
        case 7:
            cadastrarTaxistas(listaUsuarioTaxi, listaVertices);
            break;
        case 8:
            printf("Voltando ao menu principal...\n");
            return;
        default:
            printf("Opcao invalida.\n");
        }
    }
}

// Função para imprimir o menu da aplicação
void aplicacaoMenu(ListaUsuarioTaxi *listaUsuarioTaxi, ListaVertices *listaVertices, Grafo *grafo)
{
    while (1)
    {
        printf("\n \t\t\t Menu da Aplicacao \n");
        printf("1. Cadastrar cliente\n");
        printf("2. Chamar taxi\n");
        printf("3. Imprimir todos os caminhos entre dois pontos\n");
        printf("4. Imprimir melhor caminho entre dois pontos\n");
        printf("5. Imprimir menu principal\n");
        printf("Escolha uma opcao: ");

        int opcao;
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\n \t\t\t Cadastrar cliente\n");
            cadastrarCliente(listaUsuarioTaxi, listaVertices);
            break;
        case 2:
            Vertice localUsuario;
            printf("Informe a localizacao do usuario (x y): ");
            scanf("%d %d", &localUsuario.x, &localUsuario.y);

            Vertice destino;
            printf("Informe o destino desejado (x y): ");
            scanf("%d %d", &destino.x, &destino.y);

            encontrarTaxiMaisProximo(listaUsuarioTaxi, &localUsuario, &destino);

            int idTaxi;
            printf("Informe o ID do táxi para chamar: ");
            scanf("%d", &idTaxi);

            // Encontrar o táxi na lista
            Taxi *taxiChamado = NULL;
            for (int i = 0; i < listaUsuarioTaxi->numTaxis; i++)
            {
                if (listaUsuarioTaxi->taxis[i]->id == idTaxi)
                {
                    taxiChamado = listaUsuarioTaxi->taxis[i];
                    break;
                }
            }

            if (taxiChamado != NULL)
            {
                chamarTaxi(listaUsuarioTaxi, taxiChamado, &destino);
            }
            else
            {
                printf("Taxi com ID %d não encontrado na lista.\n", idTaxi);
            }
            break;
        case 3:
            printf("\n \t\t\t Imprimir todos os caminhos entre dois pontos\n");
            if (grafo->numVertices == 0)
            {
                printf("Grafo vazio. Nenhum caminho disponivel.\n");
            }
            else
            {
                int inicio, fim;
                printf("Digite o ID do ponto de inicio: ");
                scanf("%d", &inicio);
                printf("Digite o ID do ponto de destino: ");
                scanf("%d", &fim);

                if (inicio < 0 || inicio >= grafo->numVertices || fim < 0 || fim >= grafo->numVertices)
                {
                    printf("Vertices de inicio ou destino invalidos.\n");
                }
                else
                {
                    imprimirTodosCaminhos(grafo, inicio, fim);
                }
            }
            break;
        case 4:
            printf("\n \t\t\t Imprimir melhor caminho entre dois pontos\n");
            if (grafo->numVertices == 0)
            {
                printf("Grafo vazio. Nenhum caminho disponivel.\n");
            }
            else
            {
                int inicio, fim;
                printf("Digite o ID do ponto de inicio: ");
                scanf("%d", &inicio);
                printf("Digite o ID do ponto de destino: ");
                scanf("%d", &fim);

                if (inicio < 0 || inicio >= grafo->numVertices || fim < 0 || fim >= grafo->numVertices)
                {
                    printf("Vertices de inicio ou destino invalidos.\n");
                }
                else
                {
                    dijkstra(grafo, inicio, fim);
                }
            }
            break;
        case 5:
            printf("Voltando ao menu principal...\n");
            return;
        default:
            printf("Opcao invalida.\n");
        }
    }
}

// Função principal do programa
int main()
{
    // Carregar usuários do arquivo
    carregarUsuarios();

    // Inicializar estruturas de dados
    Grafo *grafo = criarGrafo(MAX_VERTICES);
    ListaVertices *listaVertices = criarListaVertices();
    ListaUsuarioTaxi *listaUsuarioTaxi = criarListaUsuarioTaxi();

    // Carregar o grafo de um arquivo
    carregarGrafoDeArquivo(grafo, "inputDados.txt");

    int opcao;
    do
    {
        // Imprimir o menu principal e ler a opção do usuário
        imprimirMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            gestaoUsuariosMenu();
            break;
        case 2:
            printf("\n");
            if (autenticarAdm())
            {
                backofficeMenu(grafo, listaUsuarioTaxi, listaVertices);
            }
            break;
        case 3:
            printf("\n\n");
            if (autenticarUsuario())
            {
                aplicacaoMenu(listaUsuarioTaxi, listaVertices, grafo);
            }
            break;
        case 4:
            printf("Saindo!\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}