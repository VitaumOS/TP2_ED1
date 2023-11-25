#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{ //Criação da struct

    int numCidades;
    int **matrizG;
} GrafoPonderado;

GrafoPonderado* alocarGrafo();
void desalocarGrafo(GrafoPonderado *);
GrafoPonderado* leGrafo(GrafoPonderado*);
void encontraCaminho(GrafoPonderado* , int*, int*, int*, int);
void imprimeCaminho(int*, int, int);

// Funções auxiliares
int* alocaCaminho(int);
int calcula_distancia(GrafoPonderado *, int*);
int caminho_contem_cidade(int*, int, int);

#endif