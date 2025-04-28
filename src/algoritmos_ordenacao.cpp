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

// Implementação Counting Sort
void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = *std::max_element(arr.begin(), arr.end()); // maior valor do array
    int min_val = *std::min_element(arr.begin(), arr.end()); // menor valor do array
    int range = max_val - min_val + 1;
    
    std::vector<int> contagem(range, 0); // cria array de contagem com o tamanho do 
    std::vector<int> saida(arr.size()); // array de saida
    
    // conta a quantidade de vezes que cada elemento aparece no array de contagem
    for (int i = 0; i < arr.size(); i++) {
        contagem[arr[i] - min_val]++;
    }
    
    // atualiza o array de contagem para que contenha as posições reais (parte de ir somando)
    for (int i = 1; i < contagem.size(); i++) {
        contagem[i] += contagem[i - 1];
    }
    
    // construindo o array de saída
    for (int i = arr.size() - 1; i >= 0; i--) {
        saida[contagem[arr[i] - min_val] - 1] = arr[i]; // faz as operações de - min_val para não 
        contagem[arr[i] - min_val]--;
    }
    
    // copia o array ordenado de volta para o array original já que estamos fazendo tudo inplace
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = saida[i];
    }
}

// Função auxiliar para o Radix Sort - ordena pelo dígito específico
// pos_decimal vai de 1, 10, 100, 1000 e assim vai
void countingSortForRadix(std::vector<int>& arr, int pos_decimal) {
    int n = arr.size();
    std::vector<int> saida(n); // cria array de saida
    std::vector<int> contagem(10, 0); // cria array de contagem (cada digito só tem 10 opções - 0 a 9)
    
    // conta no array de contagem a quantidade de vezes que cada digito aparece
    for (int i = 0; i < n; i++) {
        contagem[(arr[i] / pos_decimal) % 10]++;
    }
    
    // atualiza o array de contagem para que contenha as posições reais (parte de ir somando)
    for (int i = 1; i < 10; i++) {
        contagem[i] += contagem[i - 1];
    }
    
    // construindo o array de saída
    for (int i = n - 1; i >= 0; i--) {
        saida[contagem[(arr[i] / pos_decimal) % 10] - 1] = arr[i];
        contagem[(arr[i] / pos_decimal) % 10]--;
    }
    
    // copia o array ordenado de volta para o array original já que estamos fazendo tudo inplace
    for (int i = 0; i < n; i++) {
        arr[i] = saida[i];
    }
}

// Implementação Radix Sort
void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = *std::max_element(arr.begin(), arr.end()); // maior valor para saber o numero de digitos
    
    // counting sort para cada dígito
    for (int pos_decimal = 1; max_val / pos_decimal > 0; pos_decimal *= 10) { // multiplicando por 10 para ir para o próximo digito
        countingSortForRadix(arr, pos_decimal);
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

void mergeSortWrapper(std::vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
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
        "insertion", "selection", "quick", "merge", "bubble"
    };
}

// Mapear nome do algoritmo para função
AlgoritmoOrdenacao obterAlgoritmo(const std::string& nome) {
    static const std::unordered_map<std::string, AlgoritmoOrdenacao> algoritmos = {
        {"insertion", insertionSort},
        {"selection", selectionSort},
        {"quick", quickSortWrapper},
        {"merge", mergeSortWrapper},
        {"bubble", bubbleSort}
    };
    
    auto it = algoritmos.find(nome);
    if (it != algoritmos.end()) {
        return it->second;
    }
    
    // Algoritmo padrão se não encontrado
    return quickSortWrapper;
}

} // namespace ordenacao
