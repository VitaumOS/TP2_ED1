#include "grafo.h"

GrafoPonderado * alocarGrafo(){ //Aloca dinamicamente a struct

    GrafoPonderado *gp=malloc(sizeof(GrafoPonderado));
    return gp;
}

int* alocaCaminho( int n){

    int* caminho = malloc((n + 1) * sizeof(GrafoPonderado));
    return caminho;
}

void desalocarGrafo(GrafoPonderado *gp){ //Desaloca dinamicamente a struct
    int n=gp->numCidades;
    for(int i=0; i<n*n; i++)
        free(gp->matrizG[i]);
    free(gp->matrizG);

    free(gp);
}

GrafoPonderado *leGrafo(GrafoPonderado *gp){ //Baseado no valor n de cidade, cria-se uma matriz com a cidade de origem, destino e a distância entre elas
    
    scanf("%d", &gp->numCidades);

    int n=gp->numCidades;
    gp->matrizG=malloc(n*n*sizeof(int*)); //Aloca a matriz de adjacências n² x 3
    for(int j=0; j<n*n; j++)
        gp->matrizG[j]=malloc(3*sizeof(int));

    for(int i=0; i<n*n; i++)
        scanf("%d %d %d", &gp->matrizG[i][0], &gp->matrizG[i][1], &gp->matrizG[i][2]);
    
    return gp;
}

void imprimeCaminho(int* caminho, int numCidades, int melhor_distancia){
    for (int i = 0; i < numCidades + 1; i++){
        printf("%d ", caminho[i]);
    }
    printf("\n%d\n", melhor_distancia);
}

int calcula_distancia(GrafoPonderado *grafo, int* caminho){
    int distancia = 0;
    for (int i = 0; i < grafo->numCidades; i++){
        if(grafo->matrizG[(caminho[i] * grafo->numCidades) + caminho[i + 1]][2] == 0){
            distancia += 9999;
        }
        distancia += grafo->matrizG[(caminho[i] * grafo->numCidades) + caminho[i + 1]][2];

    }
    return distancia;
}

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