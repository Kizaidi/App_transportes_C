#ifndef ASSINATURAS_H
#define ASSINATURAS_H

#include "struct.h"

#define MAX_VERTICES 50
#define INFINITO INT_MAX

// Assinaturas das funções

// Funções relacionadas ao Grafo
Grafo *criarGrafo(int numVertices);
void adicionarAresta(Grafo *grafo, int inicio, int fim, int peso);
void removerAresta(Grafo *grafo, int inicio, int fim);

// Funções relacionadas à Lista de Usuários e Taxis
ListaUsuarioTaxi *criarListaUsuarioTaxi();
void adicionarUsuario(ListaUsuarioTaxi *lista, int id, Vertice *localizacao);
void adicionarTaxi(ListaUsuarioTaxi *lista, int id, Vertice *localizacao);

// Funções relacionadas à Lista de Vértices
ListaVertices *criarListaVertices();
void adicionarVertice(ListaVertices *lista, int id, int x, int y);

// Funções diversas
int calcularDistancia(Vertice *vertice1, Vertice *vertice2);
void chamarTaxi(ListaUsuarioTaxi *listaUsuariosTaxis, Taxi *taxi, Vertice *destino);
void encontrarTaxiMaisProximo(ListaUsuarioTaxi *listaUsuariosTaxis, Vertice *localUsuario, Vertice *destino);
void imprimirCaminho(int caminho[], int n);
void imprimirTodosCaminhosAux(Grafo *grafo, int u, int d, bool visitado[], int caminho[], int *index);
void imprimirTodosCaminhos(Grafo *grafo, int s, int d);

// Funções relacionadas ao algoritmo de Dijkstra
int minDistancia(int dist[], bool sptSet[], int V);
void dijkstra(Grafo *grafo, int src, int dest);

// Funções para carregar grafo de arquivo
void carregarGrafoDeArquivo(Grafo *grafo, const char *nomeArquivo);

// Funções adicionais para manipulação de ruas e buracos
void adicionarNovaRua(Grafo *grafo);
void removerRua(Grafo *grafo);
void adicionarBuracos(Grafo *grafo);
void removerBuracos(Grafo *grafo, int pesoOriginal);
void imprimirLocalidade(Grafo *grafo);
void imprimirTodosCaminhosSemBuracosAux(Grafo *grafo, int u, int d, bool visitado[], int caminho[], int *index);
void imprimirTodosCaminhosSemBuracos(Grafo *grafo, int s, int d);
void cadastrarTaxistas(ListaUsuarioTaxi *listaUsuariosTaxis, ListaVertices *listaVertices);

// Funções relacionadas ao gerenciamento de usuários do aplicativo
void cadastrarUsuario();
void removerUsuario();
void imprimirListaUsuarios();
void carregarUsuarios();
bool autenticarAdm();
bool autenticarUsuario();
void cadastrarCliente();

#endif // ASSINATURAS_H