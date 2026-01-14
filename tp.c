#include <stdio.h>
#include "filaprocessos.h"
int main(){

    int n;
    scanf("%d", &n);
    FilaProcessos* fila = criaFila(n);

    for(int i = 0; i < n; i++){
        adicionaFila(fila, i);
    }
    insertionSort(fila, 0);

    printf("Log CPU: \n");
    escalonador(fila);

    destroiFila(&fila);

    return 0;
}