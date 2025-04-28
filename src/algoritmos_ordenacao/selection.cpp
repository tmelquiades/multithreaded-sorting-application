#include "../../include/algoritmos_ordenacao/selection.h"

namespace ordenacao {
 
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

} // namespace ordenacao