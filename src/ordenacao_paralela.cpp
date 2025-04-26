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
    std::vector<std::thread> threads;
    
    // Função para ordenar um segmento do array
    auto ordenarSegmento = [&](int inicio, int fim) {
        std::vector<int> segmento(arr.begin() + inicio, arr.begin() + fim);
        algoritmo(segmento);
        
        // Copiar segmento ordenado de volta para o array original
        std::lock_guard<std::mutex> lock(mtx);
        std::copy(segmento.begin(), segmento.end(), arr.begin() + inicio);
    };
    
    // Criar e iniciar threads
    for (int i = 0; i < numThreads - 1; i++) {
        int inicio = i * segmentoTamanho;
        int fim = (i + 1) * segmentoTamanho;
        threads.emplace_back(ordenarSegmento, inicio, fim);
    }
    
    // Último segmento (pode ser maior devido a divisão não exata)
    int inicio = (numThreads - 1) * segmentoTamanho;
    int fim = tamanho;
    threads.emplace_back(ordenarSegmento, inicio, fim);
    
    // Aguardar todas as threads terminarem
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Mesclar os segmentos ordenados com merge
    std::vector<int> resultado = arr;
    for (int passo = 1; passo < numThreads; passo *= 2) {
        for (int i = 0; i < numThreads; i += 2 * passo) {
            int inicio = i * segmentoTamanho;
            int meio = std::min((i + passo) * segmentoTamanho, tamanho);
            int fim = std::min((i + 2 * passo) * segmentoTamanho, tamanho);
            
            if (meio < fim) {
                std::inplace_merge(resultado.begin() + inicio, resultado.begin() + meio, resultado.begin() + fim);
            }
        }
    }
    
    arr = std::move(resultado);
}

// Obter nomes de todas as estratégias disponíveis
std::vector<std::string> obterNomesEstrategias() {
    return {
        "dividir-trabalho"
    };
}

// Mapear nome da estratégia para função
EstrategiaParalela obterEstrategia(const std::string& nome) {
    static const std::unordered_map<std::string, EstrategiaParalela> estrategias = {
        {"dividir-trabalho", dividirTrabalho}
    };
    
    auto it = estrategias.find(nome);
    if (it != estrategias.end()) {
        return it->second;
    }
    
    // Estratégia padrão se não encontrada
    return dividirTrabalho;
}

} // namespace ordenacao_paralela