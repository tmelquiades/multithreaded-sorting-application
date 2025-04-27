// algoritmos_ordenacao.cpp
#include "algoritmos_ordenacao.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <unordered_map>

namespace ordenacao {

// Implementação Insertion Sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;
        
        // Move elementos do arr[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

// Implementação Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Troca o elemento mínimo encontrado com o primeiro elemento
        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
        }
    }
}

// Implementação Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool trocado;
    
    for (int i = 0; i < n - 1; i++) {
        trocado = false;
        for (int j = 0; j < n - i - 1; j++) {
            // Os pares de elementos j e j+1 são comparados
            // e trocados se estiverem se j maior que j+1
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                trocado = true;
            }
        }
        // Se não houve troca, o array já está ordenado
        if (!trocado) break;
    }
}

// Implementação Merge Sort
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

// Função auxiliar para Quick Sort
int particionar(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Pivô
    int i = (low - 1);      // Índice do menor elemento
    
    for (int j = low; j <= high - 1; j++) {
        // Se o elemento atual for menor que o pivô
        if (arr[j] < pivot) {
            i++;    // Incrementa o índice do menor elemento
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Implementação Quick Sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi é o índice de particionamento
        int pi = particionar(arr, low, high);
        
        // Ordena elementos separadamente antes e depois da partição
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Invólucros para algoritmos recursivos
void quickSortWrapper(std::vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Obter nomes de todos os algoritmos disponíveis
std::vector<std::string> obterNomesAlgoritmos() {
    return {
        "insertion", "selection", "quick"
    };
}

// Mapear nome do algoritmo para função
AlgoritmoOrdenacao obterAlgoritmo(const std::string& nome) {
    static const std::unordered_map<std::string, AlgoritmoOrdenacao> algoritmos = {
        {"insertion", insertionSort},
        {"selection", selectionSort},
        {"quick", quickSortWrapper}
    };
    
    auto it = algoritmos.find(nome);
    if (it != algoritmos.end()) {
        return it->second;
    }
    
    // Algoritmo padrão se não encontrado
    return quickSortWrapper;
}

} // namespace ordenacao
