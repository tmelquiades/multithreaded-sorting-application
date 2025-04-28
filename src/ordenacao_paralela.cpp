// ordenacao_paralela.cpp
#include "ordenacao_paralela.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <future>
#include <cmath>
#include <unordered_map>
#include <mutex>

namespace ordenacao_paralela {

// Mutex para sincronização de operações críticas
std::mutex mtx;

// Estratégia 1: Dividir o array em segmentos e ordenar cada segmento em uma thread
void dividirTrabalho(std::vector<int>& arr, ordenacao::AlgoritmoOrdenacao algoritmo, int numThreads) {
    int tamanho = arr.size();
    int segmentoTamanho = tamanho / numThreads;
    std::vector<std::thread> threads; // vetor de threads
    
    // Função para ordenar um segmento do array
    auto ordenarSegmento = [&](int inicio, int fim) {
        std::vector<int> segmento(arr.begin() + inicio, arr.begin() + fim); // criamos um array novo
        algoritmo(segmento); // ordenamos o array novo
        
        // Copiar segmento ordenado de volta para o array original
        std::lock_guard<std::mutex> lock(mtx); // usamos mutex porque estamos escrevendo no array inicial/final
        std::copy(segmento.begin(), segmento.end(), arr.begin() + inicio); // escreve de novo no array original
    };
    
    // Criar e iniciar threads
    for (int i = 0; i < numThreads - 1; i++) { // num de threads - 1 porque o ultimo segmento não sabemos o tamanho
        int inicio = i * segmentoTamanho;
        int fim = (i + 1) * segmentoTamanho;
        threads.emplace_back(ordenarSegmento, inicio, fim); // cria uma nova thread dentro do vetor threads 
                                                             // e a inicializa com a função lambda - ordenar segmento e seus parâmetros
                                                             // inicio e fim são argumentos para ordenar segmento pq precisa saber o inicio e fim dele no array
    }
    
    // Último segmento (pode ser maior devido a divisão não exata)
    int inicio = (numThreads - 1) * segmentoTamanho;
    int fim = tamanho;
    threads.emplace_back(ordenarSegmento, inicio, fim); // cria o ultimo segmento com a função lamba - ordenar segmento
    
    // Faz a thread principal aguardar todas as threads terminarem
    for (auto& thread : threads) {
        thread.join();
    }
    
    // depois que todas threads acabaram: mesclar os segmentos ordenados com merge
    std::vector<int> resultado = arr;
    for (int passo = 1; passo < numThreads; passo *= 2) {
        for (int i = 0; i < numThreads; i += 2 * passo) {
            int inicio = i * segmentoTamanho;
            int meio = std::min((i + passo) * segmentoTamanho, tamanho);
            int fim = std::min((i + 2 * passo) * segmentoTamanho, tamanho);
            
            if (meio < fim) {
                std::inplace_merge(resultado.begin() + inicio, resultado.begin() + meio, resultado.begin() + fim); // merge é inplace
            }
        }
    }
    
    arr = std::move(resultado);
}





/* ==================== Implementação paralela do QuickSort ===============================*/
int particionarParalelo(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Função auxiliar para QuickSort paralelo
void quickSortParalelo(std::vector<int>& arr, int low, int high, int profundidade, int maxProfundidade) {
    if (low < high) {
        int pi = particionarParalelo(arr, low, high);
        
        // Se a profundidade atual for menor que a profundidade máxima, cria uma thread
        if (profundidade < maxProfundidade) {
            // Ordena a parte esquerda em uma thread
            auto futureLeft = std::async(
                std::launch::async,
                quickSortParalelo,
                std::ref(arr), low, pi - 1, profundidade + 1, maxProfundidade
            );
            // Ordena a parte direita na thread atual
            quickSortParalelo(arr, pi + 1, high, profundidade + 1, maxProfundidade);
            
            futureLeft.wait();
        } else {
            // Se a profundidade máxima for atingida, ordena sequencialmente
            quickSortParalelo(arr, low, pi - 1, profundidade + 1, maxProfundidade);
            quickSortParalelo(arr, pi + 1, high, profundidade + 1, maxProfundidade);
        }
    }
}

// função de interface para QuickSort paralelo
void paralelizarQuickSort(std::vector<int>& arr, int numThreads) {
    int maxProfundidade = static_cast<int>(std::log2(numThreads));
    quickSortParalelo(arr, 0, arr.size() - 1, 0, maxProfundidade);
}

// função de interface para chamar o QuickSort paralelo
void chamarQuickSortParalelo(std::vector<int>& arr, ordenacao::AlgoritmoOrdenacao, int numThreads) {
    paralelizarQuickSort(arr, numThreads);
}



/* ==================== Implementação paralela do MergeSort ===============================*/
void mergeParalelo(std::vector<int>& arr, int inicio, int meio, int fim) {
    std::vector<int> esquerda(arr.begin() + inicio, arr.begin() + meio + 1);
    std::vector<int> direita(arr.begin() + meio + 1, arr.begin() + fim + 1);
    
    int i = 0, j = 0, k = inicio;
    // Mescla os dois vetores
    while (i < static_cast<int>(esquerda.size()) && j < static_cast<int>(direita.size())) {
        if (esquerda[i] <= direita[j]) {
            arr[k++] = esquerda[i++];
        } else {
            arr[k++] = direita[j++];
        }
    }
    
    // Copia os elementos restantes
    while (i < static_cast<int>(esquerda.size())) {
        arr[k++] = esquerda[i++];
    }
    
    while (j < static_cast<int>(direita.size())) {
        arr[k++] = direita[j++];
    }
}

void mergeSortParalelo(std::vector<int>& arr, int inicio, int fim, int profundidade, int maxProfundidade) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        
        // se a profundidade atual for menor que a profundidade máxima, cria uma thread
        if (profundidade < maxProfundidade) {
            auto futureLeft = std::async(
                std::launch::async,
                mergeSortParalelo,
                std::ref(arr), inicio, meio, profundidade + 1, maxProfundidade
            );
            mergeSortParalelo(arr, meio + 1, fim, profundidade + 1, maxProfundidade);
            
            futureLeft.wait();
        } else {
            // se a profundidade máxima for atingida, ordena sequencialmente
            mergeSortParalelo(arr, inicio, meio, profundidade + 1, maxProfundidade);
            mergeSortParalelo(arr, meio + 1, fim, profundidade + 1, maxProfundidade);
        }
        
        // mescla os dois subarrays
        mergeParalelo(arr, inicio, meio, fim);
    }
}
// função de interface para MergeSort paralelo
void paralelizarMergeSort(std::vector<int>& arr, int numThreads) {
    int maxProfundidade = static_cast<int>(std::log2(numThreads));
    mergeSortParalelo(arr, 0, arr.size() - 1, 0, maxProfundidade);
}

void chamarMergeSortParalelo(std::vector<int>& arr, ordenacao::AlgoritmoOrdenacao, int numThreads) {
    paralelizarMergeSort(arr, numThreads);
}


// obter nomes de todas as estratégias disponíveis
std::vector<std::string> obterNomesEstrategias() {
    return {
        "dividir-trabalho", "merge-paralelo", "quick-paralelo"
    };
}

// Verificar se é uma estratégia específica (não precisa de algoritmo separado)
bool ehEstrategiaEspecifica(const std::string& nome) {
    return nome == "merge-paralelo" || nome == "quick-paralelo";
}

// mapear nome da estratégia para função
EstrategiaParalela obterEstrategia(const std::string& nome) {
    static const std::unordered_map<std::string, EstrategiaParalela> estrategias = {
        {"dividir-trabalho", dividirTrabalho},
        {"merge-paralelo", chamarMergeSortParalelo},
        {"quick-paralelo", chamarQuickSortParalelo}
    };
    
    auto it = estrategias.find(nome);
    if (it != estrategias.end()) {
        return it->second;
    }
    
    // estratégia padrão se não encontrada
    return dividirTrabalho;
}

// mapear nome para estratégias específicas
EstrategiaParalelaEspecifica obterEstrategiaEspecifica(const std::string& nome) {
    static const std::unordered_map<std::string, EstrategiaParalelaEspecifica> estrategias = {
        {"merge-paralelo", paralelizarMergeSort},
        {"quick-paralelo", paralelizarQuickSort}
    };
    
    auto it = estrategias.find(nome);
    if (it != estrategias.end()) {
        return it->second;
    }
    
    // Função vazia como fallback
    return [](std::vector<int>&, int) {};
}

} // namespace ordenacao_paralela