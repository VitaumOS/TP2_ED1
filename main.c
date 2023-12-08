#include "grafo.h"


int main(){

    GrafoPonderado *gp;
    int melhor_distancia = 9999;
    
    gp = alocarGrafo(4);
    gp = leGrafo(gp);
    imprimeOrdenado(gp);
    
    return 0;
}