// benchmark.h
#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <vector>
#include <string>
#include <chrono>
#include <functional>
#include "algoritmos_ordenacao/algoritmos_ordenacao.h"
#include "ordenacao_paralela.h"

namespace benchmark {

struct ResultadoBenchmark {
    std::string nome;
    double tempo;
    bool correto;
    int tamanho;
    std::string algoritmo;
    std::string estrategia;
    int numThreads;
};

// funções de benchmark
ResultadoBenchmark benchmarkAlgoritmoSequencial( // alg sequencial
    const std::string& nomeAlgoritmo,
    std::vector<int> arr
);

ResultadoBenchmark benchmarkAlgoritmoParalelo( // alg paralelo
    const std::string& nomeAlgoritmo,
    const std::string& nomeEstrategia,
    std::vector<int> arr,
    int numThreads
);

std::vector<ResultadoBenchmark> executarBenchmarks( // juncao de varios alg
    const std::vector<std::string>& algoritmos,
    const std::vector<std::string>& estrategias,
    const std::vector<int>& tamanhos,
    int numThreads,
    int repeticoes,
    bool dadosAleatorios
);

bool verificarOrdenacao(const std::vector<int>& arr);

} // namespace benchmark

#endif // BENCHMARK_H