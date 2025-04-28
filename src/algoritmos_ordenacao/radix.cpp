#include "../../include/algoritmos_ordenacao/radix.h"
#include <algorithm>

namespace ordenacao {

// Implementação Radix Sort
void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = *std::max_element(arr.begin(), arr.end()); // maior valor para saber o numero de digitos
    
    // counting sort para cada dígito
    for (int pos_decimal = 1; max_val / pos_decimal > 0; pos_decimal *= 10) { // multiplicando por 10 para ir para o próximo digito
        countingSortForRadix(arr, pos_decimal);
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

} // namespace ordenacao