#include "../../include/algoritmos_ordenacao/merge.h"

namespace ordenacao {

// Implementação Merge Sort
void mergeSort(std::vector<int>& arr, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        
        // Ordena as duas metades
        mergeSort(arr, inicio, meio);
        mergeSort(arr, meio + 1, fim);
        
        // Mescla as duas metades
        merge(arr, inicio, meio, fim);
    }
}

void merge(std::vector<int>& arr, int inicio, int meio, int fim) {

    // Definimos o tamanho dos sub-arrays
    int tamVetorEsq = meio - inicio + 1;
    int tamVetorDir = fim - meio;
    
    std::vector<int> L(tamVetorEsq);
    std::vector<int> R(tamVetorDir);
    
    // Copiamos os dados para os sub-arrays L[] e R[]
    for (int i = 0; i < tamVetorEsq; i++)
        L[i] = arr[inicio + i];
    for (int j = 0; j < tamVetorDir; j++)
        R[j] = arr[meio + 1 + j];
    
    int i = 0, j = 0, k = inicio;
    
    // Mescla os sub-arrays de volta em arr[inicio..fim]
    while (i < tamVetorEsq && j < tamVetorDir) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copia os elementos restantes de L[], se houver
    while (i < tamVetorEsq) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < tamVetorDir) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortWrapper(std::vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

} // namespace ordenacao