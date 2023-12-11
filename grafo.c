#include "grafo.h"

GrafoPonderado * alocarGrafo(int n){ //Aloca dinamicamente o vetor de listas encadeadas

    GrafoPonderado *gp=(GrafoPonderado*)malloc(sizeof(GrafoPonderado));
    gp->cabeca = (Celula**)malloc(n*sizeof(Celula*));
    gp->ultimo = (Celula**)malloc(n*sizeof(Celula*));
    for(int i=0; i<n; i++){
        gp->cabeca[i] = (Celula*)malloc(sizeof(Celula));
        gp->cabeca[i]->prox = NULL;
        gp->ultimo[i]= gp->cabeca[i];
    }
    gp->numCidades=n;
    return gp;
}

void desalocarGrafo(GrafoPonderado ** gp){ //Desaloca dinamicamente o vetor de listas encadeadas
    int n= (*gp)->numCidades;
     for(int i = 0; i < n; i++){
            ListaDestroi(&((*gp)->cabeca[i])); // Desaloca cada lista encadeadas dado o vetor da cabesss
    }
    free((*gp)->cabeca);
    free((*gp)->ultimo);
    free(*gp);
    *gp = NULL;;
}

void ListaDestroi(Celula** cel){// Desaloca cada lista encadeadas
    Celula* aux = *cel, *aux1;
    while (aux != NULL) {
        aux1 = aux->prox;
        if (aux->item != NULL) {
            free(aux->item);
        }
        free(aux);
        aux = aux1;
    }
    *cel = NULL;
}

void leGrafo(GrafoPonderado **gp){ //Le os valores dado pelo usuario para colocar na nossa lista. De inicio, ela não está ordenada!
    int n=(*gp)->numCidades;
    int origem;
    Item item;

    for(int j=0; j<n*n; j++){
        scanf("%d%d%d", &origem, &item.cidade, &item.dist);
        ListaInsereFinal(*gp, item, origem); //Coloca o valor de cada celula no seu vetor
    }
    
}

int ListaInsereFinal(GrafoPonderado* gp, Item x, int i) { //Cria uma nova célula de a adiciona na sua devida lista
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->item = (Item*)malloc(sizeof(Item));
    if (nova == NULL)
        return 0;
    *(nova->item) = x;
    nova->prox = NULL;
    if (gp->ultimo[i] != NULL)
        gp->ultimo[i]->prox = nova;
    else
        gp->cabeca[i] = nova;
    gp->ultimo[i] = nova;
    return 1;
}

void ordenaLista(GrafoPonderado** gp) { //Com as listas criadas, ele ordena cada lista separadamente
    int n=(*gp)->numCidades;
    Celula *aux,*aux1;
    Item *aux2;
    for(int i=0; i<n; i++){
        if ((*gp)->cabeca[i]->prox == NULL) {
            return;
        }

        aux = (*gp)->cabeca[i]->prox; 

        while (aux != NULL) {
            aux1 = aux->prox;
            while(aux1 != NULL){
                if(aux->item->dist > aux1->item->dist){
                    aux2 = aux->item;
                    aux->item = aux1->item;
                    aux1->item = aux2;
    
                }
                aux1 = aux1->prox;
            }
            aux = aux->prox;
        }
    }
}

void imprimeOrdenado(GrafoPonderado* gp){//Imprime os vetores de listas encadeadas
    Celula* aux;
    for(int i=0; i<gp->numCidades; i++){
        printf("Adjacencias do verice %d: ", i);
        aux = gp->cabeca[i]->prox;
        while (aux != NULL) {
            printf("(%d, %d) -> ", aux->item->cidade, aux->item->dist);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}
