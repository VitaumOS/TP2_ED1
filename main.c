#include "grafo.h"


int main(){

    GrafoPonderado *gp;
    int  n;
    
    scanf("%d", &n);
    gp = alocarGrafo(n);
    leGrafo(&gp);
    ordenaLista(&gp);
    imprimeOrdenado(gp);
    desalocarGrafo(&gp);
    
    return 0;
}