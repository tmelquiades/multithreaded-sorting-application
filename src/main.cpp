#include "algoritmos_ordenacao/algoritmos_ordenacao.h"
#include "ordenacao_paralela.h"
#include "gerador_dados.h"
#include "benchmark.h"
#include "cli.h"

#include <iostream>
#include <string>
#include <thread>
#include <filesystem>

void printBanner() {
    std::cout << "===================================================\n";
    std::cout << "    APLICAÇÃO DE ORDENAÇÃO PARALELA EM C++         \n";
    std::cout << "===================================================\n";
    std::cout << "                                                   \n";
    std::cout << "Implementação de múltiplos algoritmos de ordenação\n";
    std::cout << "com suporte a paralelização e visualização.\n";
    std::cout << "                                                   \n";
    std::cout << "===================================================\n\n";
}

int main(int argc, char* argv[]) {
    printBanner();

    // Modo CLI
    auto opcoes = cli::parseArgumentos(argc, argv);
    cli::executarComandos(opcoes);
    
    return 0;
}