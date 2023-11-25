#include "grafo.h"


int main(){

    GrafoPonderado *gp;
    int melhor_distancia = 9999;
    
    gp = alocarGrafo();
    gp = leGrafo(gp);

    int* caminho = alocaCaminho(gp->numCidades);
    int* melhor_caminho = alocaCaminho(gp->numCidades);
    caminho[0] = melhor_caminho[0] = 0;

    encontraCaminho(gp, caminho, melhor_caminho, &melhor_distancia, 1);
    imprimeCaminho(melhor_caminho, gp->numCidades, melhor_distancia);
    
    free(melhor_caminho);
    free(caminho);
    desalocarGrafo(gp);
    return 0;
}