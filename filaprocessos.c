#include <stdio.h>
#include <stdlib.h>

#include "filaprocessos.h"

struct processo {
    int identificador;
    float tempoChegada;
    int prioridade;
    int ciclos;
};

struct filaProcessos {
    Processo *processos;
    int tam;
};

Processo filaRemove(FilaProcessos *fila, int pos);

FilaProcessos* criaFila(int n) {
    FilaProcessos *fila = (FilaProcessos* ) malloc(sizeof(FilaProcessos));
    if (fila) {
        fila->tam = n;
        fila->processos = (Processo *)malloc(sizeof(Processo) * fila->tam);
        if (!fila->processos) {
            printf("Erro ao alocar processos.\n");
            free(fila);
            return NULL;
        }
    }

    return fila;
}

void destroiFila(FilaProcessos** fila) {
    if (!fila || !*fila)
        return;

    free((*fila)->processos);
    free(*fila);
    *fila = NULL;
}

Processo filaRemove(FilaProcessos* fila, int pos) {
    Processo p = fila->processos[pos];
    for(int i = 1; i <fila->tam ; i++){
        
    
        fila->processos[i - 1] = fila->processos[i];

    }
    fila->tam--;
    return p;
}

void escalonador(FilaProcessos* fila) {
    int pos = 0;
    int ciclos = 0;
    Processo chave;  
    while(fila->tam > 0){
        chave = fila->processos[pos];
        for(int i = 0; i < 100; i++){
            fila->processos[pos].ciclos--;
            chave.ciclos--;
            ciclos++;
            if(chave.ciclos <= 0){
                Processo p = filaRemove(fila, 0);
                break;
            }
        }
        if(chave.ciclos > 0){
            fila->processos[pos].prioridade++;
            insertionSort(fila, 1);
        }
        chave.ciclos = ciclos;
        imprimeLog(chave);

        ciclos = 0;

    }

}

void imprimeLog(Processo p) {
    printf("%d %d %d\n", p.identificador, p.prioridade, p.ciclos);
}

void adicionaFila(FilaProcessos* fila, int i){
    if(fila){
        Processo process;
        scanf("%d", &process.identificador);
        scanf("%f", &process.tempoChegada);
        scanf("%d %d", &process.prioridade, &process.ciclos);

        fila->processos[i] = process; 
    }
}

//Função que realiza o insertionSort.
//Irá analisar o tempoChegada apenas se very == 0. Apenas colocaremos o very = 0 na primeira ordenação
void insertionSort(FilaProcessos* fila, int very){

    for(int i = 1; i < fila->tam; i++){
        //Vou salvar em chave o Processo que será verificado
        Processo chave = fila->processos[i];
        //Esse for é o do insertionSort normal, vou de 0 até o índice da posição sendo analisada
        for(int j = 0; j < i; j++){
            //Se a prioridade da chave analisada for menor que a da posição j
            if(chave.prioridade <= fila->processos[j].prioridade){
                if(very == 0 && chave.tempoChegada < fila->processos[j].tempoChegada){
                    // Se o tempo de chegada for menor eu faço o insertion igual acima
                    Processo salvo = chave;
                    moveAll(fila, i, j);
                    fila->processos[j] = salvo;
                    break;
                }else if(chave.prioridade < fila->processos[j].prioridade){
                    // salvo a chave
                    Processo salvo = chave;
                    //Chamo a função que move todos os elementos, da forma que o insertionSort comanda
                    moveAll(fila, i, j);
                    //Coloco o item salvo na posição correta
                    fila->processos[j] = salvo;
                    break;
                }



            }

        }
     


    }

}

//Nessa função eu movimento todos os valores do n até o j em 
void moveAll(FilaProcessos *fila, int n, int j){

    for(int i = n; i >j; i--){
        
    
        fila->processos[i] = fila->processos[i - 1];

    }


}
// 0 12 13 3 6
// 0 3 4 12 6
// 0 3 4 12 6
// j = 0
// i = 1
