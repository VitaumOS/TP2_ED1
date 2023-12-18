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
    for(int i=0; i<n; i++){//Esse for altera qual lista encadeada que vai ser ordenada
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
                else if(aux->item->dist == aux1->item->dist){
                    if(aux->item->cidade > aux1->item->cidade){
                        aux2 = aux->item;
                        aux->item = aux1->item;
                        aux1->item = aux2;
                    }
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
        printf("Adjacencias do vertice %d: ", i);
        aux = gp->cabeca[i]->prox;
        while (aux != NULL) {
            printf("(%d, %d) -> ", aux->item->cidade, aux->item->dist);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}

int* alocaCaminho(int tamanho){
    int* caminho = (int*) malloc((tamanho + 1) * sizeof(int));
    return caminho;
}

void imprimeCaminho(int* caminho, int numCidades, int melhor_distancia){//Imprime o melhor caminho e a melhor distancia
    printf("Melhor caminho:");
    for (int i = 0; i < numCidades; i++){
        printf(" %d", caminho[i]);
    }
    printf(" 0\nMelhor distancia: %d\n", melhor_distancia);
}

void encontraCaminho(GrafoPonderado* grafo, int* caminho, int* melhor_caminho, int* melhor_distancia,int percorrido){
    if(percorrido == grafo->numCidades){ // condição de fim de caminho
        caminho[percorrido] = caminho[0];
        int distancia = calcula_distancia(grafo, caminho);
        if(distancia < *melhor_distancia){
            *melhor_distancia = distancia;
            for(int i = 0; i < grafo->numCidades; i++){
                melhor_caminho[i] = caminho[i];
            }
        }
    } else {
        for (int i = 0; i < grafo->numCidades; i++){            // "Gera" a proxima cidade
            if(!caminho_contem_cidade(caminho, percorrido, i)){ // Verifica se a cidade já está presente
                caminho[percorrido] = i;                        // Inclui cidade no caminho  
                encontraCaminho(grafo, caminho, melhor_caminho, melhor_distancia, percorrido + 1);// Comando de recursão
            }
        }
        

    }
}

int caminho_contem_cidade(int* caminho, int tam, int cidade){
    for (int i = 0; i < tam; i++){
        if (caminho[i] == cidade)
            return 1;
    }
    return 0;
}

int calcula_distancia(GrafoPonderado* grafo, int* caminho){
    int distancia = 0;
    Celula* temp;
    for (int i = 0; i < grafo->numCidades; i++){ //Distancia atual -> proximo
        temp = grafo->cabeca[caminho[i]]->prox;
        while(temp->item->cidade != caminho[i + 1]){
            temp = temp->prox;
        }
        if(temp->item->dist == 0){
            distancia += 9999;
        }
        distancia += temp->item->dist;
    }
    return distancia;
}