#include "../../include/algoritmos_ordenacao/heap.h"

namespace ordenacao {

// Implementação Heap Sort com função buildMaxHeap separada
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // constroi a heap maximo
    buildMaxHeap(arr);
    
    // extrai elementos um por um do heap
    for (int i = n - 1; i > 0; i--) {
        // move a raiz atual (o maior elemento) para o final do array (parte ordenada)
        std::swap(arr[0], arr[i]);
        
        // e ajeita a heap 
        heapify(arr, i, 0);
    }
}

// Função auxiliar para o Heap Sort - heapify (ajustar um nó específico)
void heapify(std::vector<int>& arr, int n, int i) {
    int maior = i; // o maior começa como raiz
    int esquerda = 2 * i + 1; // indice do filho da esquerda
    int direita = 2 * i + 2; // indice do filho da direita
    
    // se esquerda é maior que a raiz
    if (esquerda < n && arr[esquerda] > arr[maior])
        maior = esquerda;
    
    // se direita é maior que o maior até agora
    if (direita < n && arr[direita] > arr[maior])
        maior = direita;
    
    // se o maior não é a raiz
    if (maior != i) {
        std::swap(arr[i], arr[maior]);
        
        // recursivamente heapify a subárvore afetada
        heapify(arr, n, maior);
    }
}

// Função específica para construir a heap (max-heap)
void buildMaxHeap(std::vector<int>& arr) {
    int n = arr.size();
    
    // começa do ultimo nó não-folha e transforma em heap
    // o último nó não-folha está no indice (n/2-1)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}


} // namespace ordenacao