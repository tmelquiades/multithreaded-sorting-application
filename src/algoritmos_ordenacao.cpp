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
