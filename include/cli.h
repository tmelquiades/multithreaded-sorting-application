// cli.h
#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <unordered_map>

namespace cli {

struct Opcoes {
    std::string modo;
    std::string algoritmo;
    std::string estrategia;
    std::string arquivoEntrada;
    std::string arquivoSaida;
    int tamanho;
    std::string tipoDados;
    int numThreads;
    bool visualizar;
    bool benchmark;
    std::vector<std::string> algoritmosComparar;
    std::vector<std::string> estrategiasComparar;
    std::vector<int> tamanhos;
    int repeticoes;
};

void imprimirAjuda();
Opcoes parseArgumentos(int argc, char* argv[]);
void executarComandos(const Opcoes& opcoes);
void executarOrdenacaoSimples(const Opcoes& opcoes);
void executarGeracaoDados(const Opcoes& opcoes);
void executarBenchmark(const Opcoes& opcoes);

} // namespace cli

#endif // CLI_H