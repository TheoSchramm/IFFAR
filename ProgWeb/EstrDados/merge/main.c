#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int esquerda[], int n1, int direita[], int n2)
{
    int i = 0, j = 0, k = 0;
    
    // Criação de um array do tamanho somado da parte esquerda + direita
    int *resultado = (int *)malloc((n1 + n2) * sizeof(int));

    // Mescla o lado esquerdo com o lado direito no novo array
    // Também é aqui que se é comparado qual elemento é maior que outro
    while (i < n1 && j < n2){
        if (esquerda[i] <= direita[j]){
            resultado[k] = esquerda[i];
            i++;
        }
        else{
            resultado[k] = direita[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do sub-array ESQUERDO, se houver
    while (i < n1){
        resultado[k] = esquerda[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do sub-array DIREITO, se houver
    while (j < n2){
        resultado[k] = direita[j];
        j++;
        k++;
    }

    // Copia os elementos do array "resultado" para o array original
    for (int x = 0; x < n1 + n2; x++){
        arr[x] = resultado[x];
    }

    free(resultado);
}

void merge_sort(int arr[], int size){
    if (size <= 1)
        return;

    int metade = size / 2;
    
    // Divide o array em 2 sub-arrays
    int *esquerda = (int *)malloc(metade * sizeof(int));
    int *direita = (int *)malloc((size - metade) * sizeof(int));

    // Preenche os sub-arrays recém criados com os elementos correspondentes
    for (int i = 0; i < metade; i++){
        esquerda[i] = arr[i];
    }
    for (int i = metade; i < size; i++){
        direita[i - metade] = arr[i];
    }

    // Invoca a função "merge_sort" recursivamente com os sub-arrays
    merge_sort(esquerda, metade);
    merge_sort(direita, size - metade);

    // Faz a fusão dos sub-arrays em um único array já ordenado
    merge(arr, esquerda, metade, direita, size - metade);

    free(esquerda);
    free(direita);
}

int main(){
    int vetor[] = {9, 4, 8, 5, 3, 10, 7, 1, 2, 6};
    int size = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original: ");
    for (int i = 0; i < size; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

    merge_sort(vetor, size);

    printf("Vetor ordenado: ");
    for (int i = 0; i < size; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
