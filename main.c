#include "grafo.h"


int main(){

    GrafoPonderado *gp;
    int  n;
    
    scanf("%d", &n);
    gp = alocarGrafo(n);
    
    int* caminho = alocaCaminho(n);
    int* melhor_caminho = alocaCaminho(n);
    int melhor_distancia = 9999;
    melhor_caminho[0] = caminho[0] = 0;

    leGrafo(&gp);
    ordenaLista(&gp);

    encontraCaminho(gp, caminho, melhor_caminho, &melhor_distancia, 1);

    imprimeOrdenado(gp);
    imprimeCaminho(melhor_caminho, n, melhor_distancia);
    
    free(melhor_caminho);
    free(caminho);
    desalocarGrafo(&gp);
    return 0;
}