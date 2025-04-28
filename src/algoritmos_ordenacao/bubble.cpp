#include "../../include/algoritmos_ordenacao/bubble.h"

namespace ordenacao {

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

} // namespace ordenacao