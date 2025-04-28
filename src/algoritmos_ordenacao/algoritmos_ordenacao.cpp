// algoritmos_ordenacao.cpp
#include "algoritmos_ordenacao/algoritmos_ordenacao.h"
#include "algoritmos_ordenacao/insertion.h"
#include "algoritmos_ordenacao/selection.h"
#include "algoritmos_ordenacao/bubble.h"
#include "algoritmos_ordenacao/quick.h"
#include "algoritmos_ordenacao/merge.h"
#include "algoritmos_ordenacao/heap.h"
#include "algoritmos_ordenacao/counting.h"
#include "algoritmos_ordenacao/radix.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <unordered_map>

namespace ordenacao {

// obter nomes de todos os algoritmos disponíveis
std::vector<std::string> obterNomesAlgoritmos() {
    return {
        "insertion", "selection", "quick", "merge", "bubble", "heap", "counting", "radix"
    };
}

// mapear nome do algoritmo para função
AlgoritmoOrdenacao obterAlgoritmo(const std::string& nome) {
    static const std::unordered_map<std::string, AlgoritmoOrdenacao> algoritmos = {
        {"insertion", insertionSort},
        {"selection", selectionSort},
        {"quick", quickSortWrapper},
        {"merge", mergeSortWrapper},
        {"bubble", bubbleSort},
        {"heap", heapSort},
        {"counting", countingSort},
        {"radix", radixSort}
    };
    
    auto it = algoritmos.find(nome);
    if (it != algoritmos.end()) {
        return it->second;
    }
    
    // algoritmo padrão se não encontrado
    return quickSortWrapper;
}

} // namespace ordenacao
