#ifndef STRUCT_H
#define STRUCT_H

#define USUARIOS 50    // Número máximo de usuários que podem ser cadastrados
#define VERTICES 50   // Número máximo de vértices
#define CLIENTES 50   // Número máximo de clientes que podem ser cadastrados
#define INFINITO INT_MAX

// Estrutura para armazenar informações de usuários do aplicativo
typedef struct {
    char nomeUsuario[50];
    char senha[50];
    char N; // 'A' para administrador, 'U' para usuário comum
} UsuarioAPP;

UsuarioAPP usuarios[USUARIOS]; // Array para armazenar os usuários
int numUsuarios = 0;               // Contador de usuários cadastrados

// Estrutura para armazenar informações de clientes
typedef struct {
    char nome[50];
    int localizacao; // Localização do cliente (vértice do grafo)
    char telefone[20];
} Cliente;

Cliente clientes[CLIENTES]; // Array para armazenar os clientes
int numClientes = 0;            // Contador de clientes cadastrados

// Estrutura para representar um grafo
typedef struct {
    int **matrizAdj; // Matriz de adjacência
    int numVertices; // Número de vértices
} Grafo;

// Estrutura para representar um vértice
typedef struct {
    int id;
    int x;
    int y;
} Vertice;

// Estrutura para armazenar uma lista de vértices
typedef struct {
    Vertice *vertices[VERTICES];
    int numVertices; // Número de vértices na lista
} ListaVertices;

// Estrutura para representar um táxi
typedef struct {
    int id;
    Vertice *localizacao; // Localização do táxi (vértice do grafo)
} Taxi;

// Estrutura para representar um usuário
typedef struct {
    int id;
    Vertice *localizacao; // Localização do usuário (vértice do grafo)
} Usuario;

// Estrutura para armazenar listas de usuários e táxis
typedef struct {
    Usuario *usuarios[VERTICES];
    int numUsuarios; // Número de usuários na lista
    Taxi *taxis[VERTICES];
    int numTaxis;    // Número de táxis na lista
} ListaUsuarioTaxi;

#endif // STRUCT_H
