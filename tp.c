#include <stdio.h>
#include "filaprocessos.h"
int main(){

    int n;
    scanf("%d", &n);
    FilaProcessos* fila = criaFila(n);

    for(int i = 0; i < n; i++){
        adicionaFila(fila, i);
<<<<<<< HEAD

=======
>>>>>>> 559bc6887ca4873d7d67fe1c4e9fa28e975d0242
    }
    insertionSort(fila, 0);

    printf("Log CPU: \n");
    escalonador(fila);

    destroiFila(&fila);

    return 0;
}