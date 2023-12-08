#include "grafo.h"
int ListaInsereFinal(GrafoPonderado* , Item , int );
struct grafo{ //Criação da struct

    int numCidades;
    Celula **cabeca;
    Celula **ultimo;

};
typedef struct{

    Item item;
    Celula *prox;

}Celula;

typedef struct{

    int cidade;
    int dist;
}Item;

GrafoPonderado * alocarGrafo(int n){ //Aloca dinamicamente a struct

    GrafoPonderado *gp=malloc(sizeof(GrafoPonderado));
    gp->cabeca = (Celula*)malloc(n*sizeof(Celula));
    gp->ultimo = (Celula*)malloc(n*sizeof(Celula));
    for(int i=0; i<n; i++){
        gp->cabeca[i]->prox = NULL;
        gp->ultimo[i]= gp->cabeca[i];
    }
    gp->numCidades=n;
    return gp;
}

int* alocaCaminho( int n){

    int* caminho = malloc((n + 1) * sizeof(GrafoPonderado));
    return caminho;
}

void desalocarGrafo(GrafoPonderado *gp){ //Desaloca dinamicamente a struct
    int n=gp->numCidades;
    //Arrumar essa porra dps

    free(gp);
}

GrafoPonderado *leGrafo(GrafoPonderado *gp){ //Baseado no valor n de cidade, cria-se uma matriz com a cidade de origem, destino e a distância entre elas
    
    scanf("%d", &gp->numCidades);

    int n=gp->numCidades;
    int origem;
    Item item;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d%d%d", &origem, &item.cidade, &item.dist);
            ListaInsereFinal(gp, item, origem);
        }
    }
    return gp;
}

int ListaInsereFinal(GrafoPonderado* gp, Item x, int i) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    if (nova == NULL)
        return 0;
    nova->item = x;
    nova->prox = NULL;
    gp->ultimo[i]->prox = nova;
    gp->ultimo[i] = nova;
    return 1;
}

void imprimeOrdenado(GrafoPonderado* gp){
    Celula* aux;
    for(int i=0; i<gp->numCidades; i++){
        printf("Adjacencias do verice %d: ", i);
        aux = gp->cabeca[i]->prox;
        while (aux != NULL) {
            printf("(%d, %s) -> ", aux->item.cidade, aux->item.dist);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}


void imprimeCaminho(int* caminho, int numCidades, int melhor_distancia){
    for (int i = 0; i < numCidades + 1; i++){
        printf("%d ", caminho[i]);
    }
    printf("\n%d\n", melhor_distancia);
}

//int calcula_distancia(GrafoPonderado *grafo, int* caminho){
  //  int distancia = 0;
    //for (int i = 0; i < grafo->numCidades; i++){
      //  if(grafo->matrizG[(caminho[i] * grafo->numCidades) + caminho[i + 1]][2] == 0){
        //    distancia += 9999;
        //}
        //distancia += grafo->matrizG[(caminho[i] * grafo->numCidades) + caminho[i + 1]][2];

    //}
    //return distancia;
//}

int caminho_contem_cidade(int* caminho, int posicao, int cidade){
    for (int i = 0; i < posicao; i++){
        if(caminho[i] == cidade){
            return 1;
        }
    }
    return 0;
}

void encontraCaminho(GrafoPonderado *grafo, int* caminho, int* melhor_caminho, int* melhor_distancia, int posicao){
    if(posicao == grafo->numCidades){
        caminho[posicao] = caminho[0];
        int distancia_final = calcula_distancia(grafo, caminho);
        if(distancia_final < *melhor_distancia){
            *melhor_distancia = distancia_final;
            for(int i = 0; i <= grafo->numCidades + 1; i++){
                melhor_caminho[i] = caminho[i];
            }
        }
    }
    
    for (int i = 0; i < grafo->numCidades; i++){
        if(!caminho_contem_cidade(caminho, posicao, i)){
            caminho[posicao] = i;
            encontraCaminho(grafo, caminho, melhor_caminho, melhor_distancia, posicao + 1);
        }
    }
    
}