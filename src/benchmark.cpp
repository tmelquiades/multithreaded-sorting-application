// benchmark.cpp
#include "benchmark.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace benchmark {

// verifica se um array está ordenado corretamente
bool verificarOrdenacao(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// benchmark para algoritmos sequenciais (sem uso de threads)
ResultadoBenchmark benchmarkAlgoritmoSequencial(
    const std::string& nomeAlgoritmo,
    std::vector<int> arr
) {
    ResultadoBenchmark resultado;
    resultado.nome = nomeAlgoritmo;
    
    auto algoritmo = ordenacao::obterAlgoritmo(nomeAlgoritmo); // obter o algoritmo de ordenação
    
    // medir o tempo de execução
    auto inicio = std::chrono::high_resolution_clock::now();
    
    algoritmo(arr); // executa o algoritmo
    
    auto fim = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    
    resultado.tempo = duracao.count();
    resultado.correto = verificarOrdenacao(arr);
    
    return resultado; // o nome e tempo que levou
}

// benchmark para algoritmos paralelos (com uso de threads)
ResultadoBenchmark benchmarkAlgoritmoParalelo(
    const std::string& nomeAlgoritmo,
    const std::string& nomeEstrategia,
    std::vector<int> arr,
    int numThreads
) {
    ResultadoBenchmark resultado;
    std::ostringstream nomeCompleto;
    nomeCompleto << nomeAlgoritmo << " + " << nomeEstrategia << " (" << numThreads << " threads)";
    resultado.nome = nomeCompleto.str();
    
    // medir o tempo de execução
    auto inicio = std::chrono::high_resolution_clock::now();
    
    if (ordenacao_paralela::ehEstrategiaEspecifica(nomeEstrategia)) {
        auto estrategia = ordenacao_paralela::obterEstrategiaEspecifica(nomeEstrategia);
        estrategia(arr, numThreads); // executa o algoritmo de paralelizacao especifico com o num de threads escolhido
    } else {
        auto algoritmo = ordenacao::obterAlgoritmo(nomeAlgoritmo);
        auto estrategia = ordenacao_paralela::obterEstrategia(nomeEstrategia);
        estrategia(arr, algoritmo, numThreads); // executa o dividirTrabalho com o num de threads escolhido (esse é o unico que nao eh especifico)
    }
    
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    
    resultado.tempo = duracao.count();
    resultado.correto = verificarOrdenacao(arr);
    
    return resultado;
}

// gerar dados aleatórios para teste
std::vector<int> gerarDadosAleatorios(int tamanho, int min = 0, int max = 1000000) {
    std::vector<int> arr(tamanho); // array do tamanho escolhido
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    
    for (int i = 0; i < tamanho; i++) {
        arr[i] = dist(gen);
    }
    
    return arr;
}

// executar benchmarks completos
std::vector<ResultadoBenchmark> executarBenchmarks(
    const std::vector<std::string>& algoritmos,
    const std::vector<std::string>& estrategias,
    const std::vector<int>& tamanhos,
    int numThreads,
    int repeticoes,
    bool dadosAleatorios
) {
    std::vector<ResultadoBenchmark> resultados;
    
    // para cada tamanho de array
    for (int tamanho : tamanhos) {
        // criar dados de entrada
        std::vector<int> dadosOriginais;
        if (dadosAleatorios) {
            dadosOriginais = gerarDadosAleatorios(tamanho);
        } else {
            // criar array ordenado inversamente para caso pior
            dadosOriginais.resize(tamanho);
            for (int i = 0; i < tamanho; i++) {
                dadosOriginais[i] = tamanho - i;
            }
        }
        
        // benchmark para cada algoritmo sequencial
        for (const auto& algoritmo : algoritmos) {
            double tempoTotal = 0.0;
            bool todosCorretos = true;
            
            // executar repetidas vezes
            for (int i = 0; i < repeticoes; i++) {
                auto dadosCopia = dadosOriginais;
                auto resultado = benchmarkAlgoritmoSequencial(algoritmo, dadosCopia); // executa todos algs sequencialmente
                tempoTotal += resultado.tempo;
                todosCorretos = todosCorretos && resultado.correto;
            }
            // calcular o tempo médio e verificar se todos os resultados estão corretos
            ResultadoBenchmark resultadoMedio;
            resultadoMedio.nome = algoritmo + " (n=" + std::to_string(tamanho) + ")";
            resultadoMedio.tempo = tempoTotal / repeticoes;
            resultadoMedio.correto = todosCorretos;
            
            resultados.push_back(resultadoMedio);
        }
        
        // benchmark para cada combinação de algoritmo e estratégia paralela para todos
        // para os algoritmos que tem estrategia especifica executa 2 vezes (especifica e dividirTrabalho)
        for (const auto& algoritmo : algoritmos) {
            for (const auto& estrategia : estrategias) {
                if (ordenacao_paralela::ehEstrategiaEspecifica(estrategia) && 
                    !(estrategia == "merge-paralelo" && algoritmo == "merge") && 
                    !(estrategia == "quick-paralelo" && algoritmo == "quick")) {
                    continue;  // pular combinações que não fazem sentido (só faço estratégia especifica com quem dá)
                }
                // executar benchmark para cada combinação de algoritmo e estratégia
                double tempoTotal = 0.0;
                bool todosCorretos = true;
                // executar repetidas vezes
                for (int i = 0; i < repeticoes; i++) {
                    auto dadosCopia = dadosOriginais;
                    auto resultado = benchmarkAlgoritmoParalelo(algoritmo, estrategia, dadosCopia, numThreads); // executa o algoritmo
                    tempoTotal += resultado.tempo;
                    todosCorretos = todosCorretos && resultado.correto; // vai acumulando os true de todos
                }
                              
                ResultadoBenchmark resultadoMedio;
                std::ostringstream nomeCompleto;
                nomeCompleto << algoritmo << " + " << estrategia << " (n=" << tamanho << ", " << numThreads << " threads)";
                resultadoMedio.nome = nomeCompleto.str();
                resultadoMedio.tempo = tempoTotal / repeticoes; // média dos tempos das repetições
                resultadoMedio.correto = todosCorretos;
                
                resultados.push_back(resultadoMedio); // adiciona o resultado desse algoritmo + estratégia a resultados
            }
        }
    }
    
    return resultados;
}

} // namespace benchmark