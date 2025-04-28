#include "../../include/algoritmos_ordenacao/counting.h"
#include <algorithm>

namespace ordenacao {

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

} // namespace ordenacao