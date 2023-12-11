#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct grafo GrafoPonderado;
typedef struct celula Celula;
typedef struct item Item;


struct grafo{ //Criação da struct

    int numCidades;
    Celula **cabeca;
    Celula **ultimo;

};
struct celula{

    struct item *item;
    struct celula *prox;

};

struct item{

    int cidade;
    int dist;
};

void imprimeOrdenado(GrafoPonderado*);
int ListaInsereFinal(GrafoPonderado* , Item, int );
GrafoPonderado* alocarGrafo();
void ordenaLista(GrafoPonderado**);
void ListaDestroi(Celula** );
void desalocarGrafo(GrafoPonderado **);
void leGrafo(GrafoPonderado**);
void encontraCaminho(GrafoPonderado* , int*, int*, int*, int);
void imprimeCaminho(int*, int, int);

// Funções auxiliares
int* alocaCaminho(int);
int calcula_distancia(GrafoPonderado *, int*);
int caminho_contem_cidade(int*, int, int);

#endif