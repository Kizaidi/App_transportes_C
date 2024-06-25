#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "struct.h"
#include "assinaturas.h"

Grafo *criarGrafo(int numVertices)
{
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->matrizAdj = (int **)malloc(numVertices * sizeof(int *));

    for (int i = 0; i < numVertices; i++)
    {
        grafo->matrizAdj[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++)
        {
            grafo->matrizAdj[i][j] = (i == j) ? 0 : INFINITO;
        }
    }

    return grafo;
}

void adicionarAresta(Grafo *grafo, int inicio, int fim, int peso)
{
    if (inicio >= 0 && inicio < grafo->numVertices && fim >= 0 && fim < grafo->numVertices)
    {
        grafo->matrizAdj[inicio][fim] = peso;
        grafo->matrizAdj[fim][inicio] = peso; // Grafo não direcionado
    }
}

void removerAresta(Grafo *grafo, int inicio, int fim)
{
    if (inicio >= 0 && inicio < grafo->numVertices && fim >= 0 && fim < grafo->numVertices)
    {
        grafo->matrizAdj[inicio][fim] = INFINITO;
        grafo->matrizAdj[fim][inicio] = INFINITO; // Grafo não direcionado
    }
}

ListaUsuarioTaxi *criarListaUsuarioTaxi()
{
    ListaUsuarioTaxi *lista = (ListaUsuarioTaxi *)malloc(sizeof(ListaUsuarioTaxi));
    lista->numUsuarios = 0;
    lista->numTaxis = 0;
    return lista;
}

void adicionarUsuario(ListaUsuarioTaxi *lista, int id, Vertice *localizacao)
{
    if (lista->numUsuarios < VERTICES)
    {
        Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
        usuario->id = id;
        usuario->localizacao = localizacao;
        lista->usuarios[lista->numUsuarios++] = usuario;
    }
}

void adicionarTaxi(ListaUsuarioTaxi *lista, int id, Vertice *localizacao)
{
    if (lista->numTaxis < VERTICES)
    {
        Taxi *taxi = (Taxi *)malloc(sizeof(Taxi));
        taxi->id = id;
        taxi->localizacao = localizacao;
        lista->taxis[lista->numTaxis++] = taxi;
    }
}

ListaVertices *criarListaVertices()
{
    ListaVertices *lista = (ListaVertices *)malloc(sizeof(ListaVertices));
    lista->numVertices = 0;
    return lista;
}

void adicionarVertice(ListaVertices *lista, int id, int x, int y)
{
    if (lista->numVertices < VERTICES)
    {
        Vertice *vertice = (Vertice *)malloc(sizeof(Vertice));
        vertice->id = id;
        vertice->x = x;
        vertice->y = y;
        lista->vertices[lista->numVertices++] = vertice;
    }
}

int calcularDistancia(Vertice *vertice1, Vertice *vertice2)
{
    // Exemplo simplificado: Distância euclidiana
    return abs(vertice1->x - vertice2->x) + abs(vertice1->y - vertice2->y);
}

void chamarTaxi(ListaUsuarioTaxi *listaUsuariosTaxis, Taxi *taxi, Vertice *destino)
{
    int custo = calcularDistancia(listaUsuariosTaxis->usuarios[taxi->id]->localizacao, destino) * 2; // Exemplo de cálculo de custo
    printf("Custo estimado da viagem: %d\n", custo);

    // Atualizar a localização do táxi para o destino
    listaUsuariosTaxis->usuarios[taxi->id]->localizacao = destino;
    printf("Localizacao atual do taxi: (%d, %d)\n", destino->x, destino->y);
}

void encontrarTaxiMaisProximo(ListaUsuarioTaxi *listaUsuariosTaxis, Vertice *localUsuario, Vertice *destino)
{
    Taxi *taxiMaisProximo = NULL;
    int menorDistancia = INFINITO;

    for (int i = 0; i < listaUsuariosTaxis->numTaxis; i++)
    {
        Taxi *taxi = listaUsuariosTaxis->taxis[i];
        int distancia = calcularDistancia(listaUsuariosTaxis->usuarios[taxi->id]->localizacao, localUsuario);
        if (distancia < menorDistancia)
        {
            menorDistancia = distancia;
            taxiMaisProximo = taxi;
        }
    }

    Vertice *localizacaoTaxi = listaUsuariosTaxis->usuarios[taxiMaisProximo->id]->localizacao;
    printf("Taxi mais proximo está localizado em (%d, %d)\n", localizacaoTaxi->x, localizacaoTaxi->y);

    // Simulando chamada do táxi após encontrar o mais próximo
    chamarTaxi(listaUsuariosTaxis, taxiMaisProximo, destino);
}

void imprimirCaminho(int caminho[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", caminho[i]);
    }
    printf("\n");
}

void imprimirTodosCaminhosAux(Grafo *grafo, int u, int d, bool visitado[], int caminho[], int *index)
{
    visitado[u] = true;
    caminho[(*index)++] = u;

    if (u == d)
    {
        imprimirCaminho(caminho, *index);
    }
    else
    {
        for (int i = 0; i < grafo->numVertices; i++)
        {
            if (!visitado[i] && grafo->matrizAdj[u][i] != INFINITO)
            {
                imprimirTodosCaminhosAux(grafo, i, d, visitado, caminho, index);
            }
        }
    }

    (*index)--;
    visitado[u] = false;
}

void imprimirTodosCaminhos(Grafo *grafo, int s, int d)
{
    bool *visitado = (bool *)malloc(grafo->numVertices * sizeof(bool));
    int *caminho = (int *)malloc(grafo->numVertices * sizeof(int));
    int index = 0;

    for (int i = 0; i < grafo->numVertices; i++)
    {
        visitado[i] = false;
    }

    imprimirTodosCaminhosAux(grafo, s, d, visitado, caminho, &index);

    free(visitado);
    free(caminho);
}

int minDistancia(int dist[], bool sptSet[], int V)
{
    int min = INFINITO, min_index;

    for (int v = 0; v < V; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void dijkstra(Grafo *grafo, int src, int dest)
{
    int V = grafo->numVertices;
    int dist[V];
    bool sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        parent[src] = -1;
        dist[i] = INFINITO;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistancia(dist, sptSet, V);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && grafo->matrizAdj[u][v] && dist[u] != INFINITO && dist[u] + grafo->matrizAdj[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + grafo->matrizAdj[u][v];
            }
        }
    }

    printf("Melhor caminho de %d até %d com custo %d: ", src, dest, dist[dest]);
    int crawl = dest;
    while (parent[crawl] != -1)
    {
        printf("%d <- ", crawl);
        crawl = parent[crawl];
    }
    printf("%d\n", src);
}

void carregarGrafoDeArquivo(Grafo *grafo, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int V, E;
    fscanf(arquivo, "%d %d", &V, &E);
    for (int i = 0; i < E; i++)
    {
        int inicio, fim, peso;
        fscanf(arquivo, "%d %d %d", &inicio, &fim, &peso);
        adicionarAresta(grafo, inicio, fim, peso);
    }
    fclose(arquivo);
}

void adicionarNovaRua(Grafo *grafo)
{
    int inicio, fim, peso;
    printf("Digite o id do vertice de inicio: ");
    scanf("%d", &inicio);
    printf("Digite o id do vertice de fim: ");
    scanf("%d", &fim);
    printf("Digite o peso da aresta (distancia): ");
    scanf("%d", &peso);

    adicionarAresta(grafo, inicio, fim, peso);
    printf("Rua adicionada com sucesso!\n");
}

void removerRua(Grafo *grafo)
{
    int inicio, fim;
    printf("Digite o id do vertice de inicio: ");
    scanf("%d", &inicio);
    printf("Digite o id do vertice de fim: ");
    scanf("%d", &fim);

    removerAresta(grafo, inicio, fim);
    printf("Rua removida com sucesso!\n");
}

void adicionarBuracos(Grafo *grafo)
{
    int inicio, fim;
    printf("Digite o id do vertice de inicio: ");
    scanf("%d", &inicio);
    printf("Digite o id do vertice de fim: ");
    scanf("%d", &fim);

    grafo->matrizAdj[inicio][fim] = -1;
    grafo->matrizAdj[fim][inicio] = -1;
    printf("Buracos adicionados na rua com sucesso!\n");
}

void removerBuracos(Grafo *grafo, int pesoOriginal)
{
    int inicio, fim;
    printf("Digite o id do vertice de inicio: ");
    scanf("%d", &inicio);
    printf("Digite o id do vertice de fim: ");
    scanf("%d", &fim);

    grafo->matrizAdj[inicio][fim] = pesoOriginal;
    grafo->matrizAdj[fim][inicio] = pesoOriginal;
    printf("Buracos removidos da rua com sucesso!\n");
}

void imprimirLocalidade(Grafo *grafo)
{
    printf("Localidade (Grafo de ruas):\n");
    for (int i = 0; i < grafo->numVertices; i++)
    {
        for (int j = 0; j < grafo->numVertices; j++)
        {
            if (grafo->matrizAdj[i][j] != INFINITO && grafo->matrizAdj[i][j] != 0)
            {
                printf("Rua de %d para %d com peso %d\n", i, j, grafo->matrizAdj[i][j]);
            }
        }
    }
}

void imprimirTodosCaminhosSemBuracosAux(Grafo *grafo, int u, int d, bool visitado[], int caminho[], int *index)
{
    visitado[u] = true;
    caminho[(*index)++] = u;

    if (u == d)
    {
        imprimirCaminho(caminho, *index);
    }
    else
    {
        for (int i = 0; i < grafo->numVertices; i++)
        {
            if (!visitado[i] && grafo->matrizAdj[u][i] != INFINITO && grafo->matrizAdj[u][i] != -1)
            {
                imprimirTodosCaminhosSemBuracosAux(grafo, i, d, visitado, caminho, index);
            }
        }
    }

    (*index)--;
    visitado[u] = false;
}

void imprimirTodosCaminhosSemBuracos(Grafo *grafo, int s, int d)
{
    bool *visitado = (bool *)malloc(grafo->numVertices * sizeof(bool));
    int *caminho = (int *)malloc(grafo->numVertices * sizeof(int));
    int index = 0;

    for (int i = 0; i < grafo->numVertices; i++)
    {
        visitado[i] = false;
    }

    imprimirTodosCaminhosSemBuracosAux(grafo, s, d, visitado, caminho, &index);

    free(visitado);
    free(caminho);
}

void cadastrarTaxistas(ListaUsuarioTaxi *listaUsuariosTaxis, ListaVertices *listaVertices)
{
    int id, verticeId;
    printf("Digite o id do taxista: ");
    scanf("%d", &id);
    printf("Digite o id do vertice onde o taxista esta localizado: ");
    scanf("%d", &verticeId);

    if (verticeId >= 0 && verticeId < listaVertices->numVertices)
    {
        adicionarTaxi(listaUsuariosTaxis, id, listaVertices->vertices[verticeId]);
        printf("Taxista cadastrado com sucesso!\n");
    }
    else
    {
        printf("Vertice invalido.\n");
    }
}

// Função para cadastrar um novo usuário
void cadastrarUsuario()
{
    if (numUsuarios >= USUARIOS)
    {
        printf("Nao e possivel cadastrar mais usuarios. Limite excedido.\n");
        return;
    }

    printf("Digite o nome de usuario: ");
    scanf(" %[^\n]s", usuarios[numUsuarios].nomeUsuario);

    printf("Digite a senha: ");
    scanf(" %[^\n]s", usuarios[numUsuarios].senha);

    printf("Digite o tipo de usuario (A para administrador, U para usuario comum): ");
    scanf(" %c", &usuarios[numUsuarios].N);

    // Verifica se o tipo inserido é válido ('A' ou 'U')
    if (usuarios[numUsuarios].N != 'A' && usuarios[numUsuarios].N != 'U')
    {
        printf("N de usuario invalido. Use 'A' para administrador ou 'U' para usuario comum.\n");
        return;
    }

    // Abrir o arquivo para escrita em modo append ("a")
    FILE *arquivoUsuarios = fopen("User.txt", "a");
    if (arquivoUsuarios == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    // Escrever o novo usuário no arquivo
    fprintf(arquivoUsuarios, "%s %s %c\n", usuarios[numUsuarios].nomeUsuario, usuarios[numUsuarios].senha, usuarios[numUsuarios].N);

    // Fechar o arquivo
    fclose(arquivoUsuarios);

    numUsuarios++;
    printf("Usuario cadastrado com sucesso.\n");
}

// Função para remover um usuário pelo nome de usuário
void removerUsuario()
{
    if (numUsuarios == 0)
    {
        printf("Nao ha usuarios para remover.\n");
        return;
    }

    char nomeUsuarioRemover[50];
    printf("Digite o nome de usuario a remover: ");
    scanf(" %[^\n]s", nomeUsuarioRemover);

    // Abrir o arquivo para leitura e um arquivo temporário para escrita
    FILE *arquivoUsuarios = fopen("User.txt", "r");
    if (arquivoUsuarios == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    FILE *temporario = fopen("cache.txt", "w");
    if (temporario == NULL)
    {
        printf("Erro ao abrir o arquivo temporario.\n");
        fclose(arquivoUsuarios);
        return;
    }

    bool encontrado = false;
    char linha[150]; // Tamanho arbitrário para a linha do arquivo
    while (fgets(linha, sizeof(linha), arquivoUsuarios) != NULL)
    {
        char nomeArquivo[50], senhaArquivo[50], tipoArquivo;
        sscanf(linha, "%s %s %c", nomeArquivo, senhaArquivo, &tipoArquivo);

        // Comparar o nome de usuário para encontrar o usuário a ser removido
        if (strcmp(nomeUsuarioRemover, nomeArquivo) != 0)
        {
            fprintf(temporario, "%s %s %c\n", nomeArquivo, senhaArquivo, tipoArquivo);
        }
        else
        {
            encontrado = true;
        }
    }

    fclose(arquivoUsuarios);
    fclose(temporario);

    // Remover o arquivo original e renomear o arquivo temporário para o original
    remove("User.txt");
    rename("cache.txt", "User.txt");

    if (encontrado)
    {
        // Atualizar o array de usuários removendo o último elemento
        numUsuarios--;
        printf("Usuario removido com sucesso.\n");
    }
    else
    {
        printf("Usuario nao encontrado.\n");
    }
}

// Função para imprimir a lista de usuários cadastrados
void imprimirListaUsuarios()
{
    FILE *arquivoUsuarios = fopen("User.txt", "r");
    if (arquivoUsuarios == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    printf("__________ Lista de Usuarios \n");
    char linha[150]; // Tamanho arbitrário para a linha do arquivo
    while (fgets(linha, sizeof(linha), arquivoUsuarios) != NULL)
    {
        char nomeArquivo[50], senhaArquivo[50], tipoArquivo;
        sscanf(linha, "%s %s %c", nomeArquivo, senhaArquivo, &tipoArquivo);
        printf("\t\t Nome de Usuario: %s | Senha: %s | Nivel: %c\n", nomeArquivo, senhaArquivo, tipoArquivo);
    }

    fclose(arquivoUsuarios);
}

// Função para carregar os usuários a partir de um arquivo
void carregarUsuarios()
{
    FILE *arquivoUsuarios = fopen("User.txt", "r");
    if (arquivoUsuarios == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    while (fscanf(arquivoUsuarios, "%s %s %c\n", usuarios[numUsuarios].nomeUsuario, usuarios[numUsuarios].senha, &usuarios[numUsuarios].N) != EOF)
    {
        numUsuarios++;
        if (numUsuarios >= USUARIOS)
        {
            printf("Limite de usuarios excedido. Alguns usuarios nao foram carregados.\n");
            break;
        }
    }

    fclose(arquivoUsuarios);
}

// Função para autenticar o administrador
bool autenticarAdm()
{
    char nomeUsuario[50];
    char senha[50];

    printf("Digite o nome de usuario: ");
    scanf(" %[^\n]s", nomeUsuario);

    printf("Digite a senha: ");
    scanf(" %[^\n]s", senha);

    for (int i = 0; i < numUsuarios; i++)
    {
        if (usuarios[i].N == 'A' && strcmp(usuarios[i].nomeUsuario, nomeUsuario) == 0 && strcmp(usuarios[i].senha, senha) == 0)
        {
            return true; // Administrador autenticado com sucesso
        }
    }
    return false; // Administrador não encontrado ou senha incorreta
}

// Função para autenticar o usuário comum
bool autenticarUsuario()
{

    char nomeUsuario[50];
    char senha[50];

    printf("Digite o nome de usuario: ");
    scanf(" %[^\n]s", nomeUsuario);

    printf("Digite a senha: ");
    scanf(" %[^\n]s", senha);
    for (int i = 0; i < numUsuarios; i++)
    {
        if (usuarios[i].N == 'U' && strcmp(usuarios[i].nomeUsuario, nomeUsuario) == 0 && strcmp(usuarios[i].senha, senha) == 0)
        {
            return true; // Usuário autenticado com sucesso
        }
    }
    return false; // Usuário não encontrado ou senha incorreta
}


// Função para cadastrar um novo cliente, incluindo localização
void cadastrarCliente()
{
    if (numClientes >= CLIENTES)
    {
        printf("Nao e possivel cadastrar mais clientes. Limite excedido.\n");
        return;
    }

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", clientes[numClientes].nome);

    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]s", clientes[numClientes].telefone);

    printf("Digite a localizacao do cliente (numero do vertice do grafo): ");
    scanf(" %d", &clientes[numClientes].localizacao);

    // Abrir o arquivo para escrita em modo append ("a")
    FILE *arquivoClientes = fopen("clientes.txt", "a");
    if (arquivoClientes == NULL)
    {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    // Escrever o novo cliente no arquivo
    fprintf(arquivoClientes, "%s;%d;%s\n", clientes[numClientes].nome, clientes[numClientes].localizacao, clientes[numClientes].telefone);

    // Fechar o arquivo
    fclose(arquivoClientes);

    numClientes++;
    printf("Cliente cadastrado com sucesso.\n");
}


#endif