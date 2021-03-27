//
// Created by samuel on 3/25/21.
//

#include "grafomatadjexercicio.h"

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>




typedef struct Aresta {
    int origem;
    int destino;
} Aresta;

void inicializarMatriz(GrafoMatrizAdj *grafo);

void verificarGrafoNulo(GrafoMatrizAdj *grafo);

Aresta *obterAresta(GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino);

GrafoMatrizAdj *inicializar(int numVertices, bool ponderado) {
    GrafoMatrizAdj *grafo = malloc(sizeof(GrafoMatrizAdj));

    grafo->arestas = (int **) malloc(numVertices * sizeof(int *));
    grafo->rotuloVertices = (char **) malloc(numVertices * sizeof(char *));
    grafo->maxNumVertices = numVertices;
    grafo->verticesInseridos = 0;
    grafo->ponderado = ponderado;

    inicializarMatriz(grafo);

    return grafo;
}

void inicializarMatriz(GrafoMatrizAdj *grafo) {
    for (int i = 0; i < grafo->maxNumVertices; i++) {
        grafo->arestas[i] = (int *) malloc(grafo->maxNumVertices * sizeof(int));
        grafo->rotuloVertices[i] = NULL;

        for (int j = 0; j < grafo->maxNumVertices; j++) {
            grafo->arestas[i][j] = grafo->ponderado ? INT_MAX : 0;
        }
    }
}

void verificarGrafoNulo(GrafoMatrizAdj *grafo) {
    if (grafo != NULL)
        return;

    printf("Você inseriu um grafo nulo !!");
    exit(SIGILL);
}


/**
 * A principio nao temos nenhuma ordenacao usando os rotulos.
 * Portanto, usaremos busca linear
 **/
int obterIndiceVertice(GrafoMatrizAdj *grafo, char *rotuloVertice) {
    verificarGrafoNulo(grafo);

    for (int i = 0; i < grafo->maxNumVertices; i++) {
        if (grafo->rotuloVertices[i] == NULL)
            continue;
        if (strcmp(grafo->rotuloVertices[i], rotuloVertice) == 0)
            return i;
    }

    return -1;
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de vertices que ja foi inserido no grafo.
 * Logo, ela pode/deve ser usada para especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(GrafoMatrizAdj *grafo, char *rotuloVertice) {
    verificarGrafoNulo(grafo);
    if (rotuloVertice == NULL)
        return;

    grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
    grafo->verticesInseridos++;

}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da aresta.
 * Se o grafo for não ponderado, passaremos o valor 1 para a variavel peso, de modo que represente existência da aresta.
 * Se um dos rotulos dos vertices nao existir, simplesmente nao faremos nada.
 **/

void inserirAresta(GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino, int peso) {

    if (rotuloVOrigem == NULL || rotuloVDestino == NULL)
        return;

    peso = grafo->ponderado ? 1 : peso;


    Aresta *aresta = obterAresta(grafo, rotuloVOrigem, rotuloVDestino);

    if (aresta->destino == -1 || aresta->origem == -1)
        return;

    grafo->arestas[aresta->destino][aresta->origem] = peso;
    grafo->arestas[aresta->origem][aresta->destino] = peso;

    free(aresta);

}

Aresta *obterAresta(GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino) {

    Aresta *aresta = malloc(sizeof(Aresta));

    aresta->origem = obterIndiceVertice(grafo, rotuloVOrigem);
    aresta->destino = obterIndiceVertice(grafo, rotuloVDestino);

    return aresta;
}


/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois vertices em um grafo ponderado,
 * e haver conexão entre dois vertices em um grafo nao-ponderado.
 **/
bool saoConectados(GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino) {
    verificarGrafoNulo(grafo);

    bool conectados = false;

    if (rotuloVDestino == NULL || rotuloVOrigem == NULL)
        return conectados;


    Aresta *aresta = obterAresta(grafo, rotuloVOrigem, rotuloVDestino);


    if (aresta->origem == -1 || aresta->destino == -1)
        return conectados;

    if (grafo->ponderado)
        conectados = grafo->arestas[aresta->origem][aresta->destino] != INT_MAX;
    else
        conectados = grafo->arestas[aresta->origem][aresta->destino] != 0;

    free(aresta);

    return conectados;

}