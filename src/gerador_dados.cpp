#include "gerador_dados.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace gerador {

// Função para gerar dados aleatórios
std::vector<int> gerarAleatorio(int tamanho, int min = 0, int max = 1000000) {
    std::vector<int> dados(tamanho);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    
    for (int i = 0; i < tamanho; i++) {
        dados[i] = dist(gen);
    }
    
    return dados;
}

// Gerar array ordenado
std::vector<int> gerarOrdenado(int tamanho) {
    std::vector<int> dados(tamanho);
    for (int i = 0; i < tamanho; i++) {
        dados[i] = i;
    }
    return dados;
}

// Gerar array ordenado inversamente
std::vector<int> gerarOrdenadoInversamente(int tamanho) {
    std::vector<int> dados(tamanho);
    for (int i = 0; i < tamanho; i++) {
        dados[i] = tamanho - i - 1;
    }
    return dados;
}

// Gerar array parcialmente ordenado
std::vector<int> gerarParcialmenteOrdenado(int tamanho) {
    std::vector<int> dados = gerarOrdenado(tamanho);
    
    // Embaralhar apenas 30% dos elementos
    int numeroElementosEmbaralhados = tamanho * 0.3;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < numeroElementosEmbaralhados; i++) {
        int idx1 = std::uniform_int_distribution<>(0, tamanho - 1)(gen);
        int idx2 = std::uniform_int_distribution<>(0, tamanho - 1)(gen);
        std::swap(dados[idx1], dados[idx2]);
    }
    
    return dados;
}

// Gerar array com muitos valores repetidos
std::vector<int> gerarRepetido(int tamanho) {
    std::vector<int> dados(tamanho);
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Usar apenas 10% do tamanho como valores únicos possíveis
    int valoresUnicos = std::max(5, tamanho / 10);
    std::uniform_int_distribution<> dist(0, valoresUnicos - 1);
    
    for (int i = 0; i < tamanho; i++) {
        dados[i] = dist(gen);
    }
    
    return dados;
}

// Gerar array com distribuição não uniforme (distribuição normal)
std::vector<int> gerarDistribuido(int tamanho) {
    std::vector<int> dados(tamanho);
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Usar distribuição normal centrada em 500000 com desvio padrão de 100000
    std::normal_distribution<> dist(500000.0, 100000.0);
    
    for (int i = 0; i < tamanho; i++) {
        dados[i] = static_cast<int>(std::abs(dist(gen)));
    }
    
    return dados;
}

// Função principal para gerar dados com base no tipo
std::vector<int> gerarDados(int tamanho, TipoDados tipo) {
    switch (tipo) {
        case ALEATORIO:
            return gerarAleatorio(tamanho);
        case ORDENADO:
            return gerarOrdenado(tamanho);
        case ORDENADO_INVERSAMENTE:
            return gerarOrdenadoInversamente(tamanho);
        case PARCIALMENTE_ORDENADO:
            return gerarParcialmenteOrdenado(tamanho);
        case REPETIDO:
            return gerarRepetido(tamanho);
        case DISTRIBUIDO:
            return gerarDistribuido(tamanho);
        default:
            return gerarAleatorio(tamanho);
    }
}

// Ler dados de um arquivo
std::vector<int> lerArquivo(const std::string& caminho) {
    std::vector<int> dados;
    std::ifstream arquivo(caminho);
    
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo: " + caminho);
    }
    
    int valor;
    while (arquivo >> valor) {
        dados.push_back(valor);
    }
    
    arquivo.close();
    return dados;
}

// Salvar dados em um arquivo
bool salvarArquivo(const std::vector<int>& dados, const std::string& caminho) {
    std::ofstream arquivo(caminho);
    
    if (!arquivo.is_open()) {
        return false;
    }
    
    for (size_t i = 0; i < dados.size(); i++) {
        arquivo << dados[i];
        if (i < dados.size() - 1) {
            arquivo << "\n";
        }
    }
    
    arquivo.close();
    return true;
}

// Obter o nome amigável de um tipo de dados
std::string obterNomeTipo(TipoDados tipo) {
    switch (tipo) {
        case ALEATORIO: return "aleatorio";
        case ORDENADO: return "ordenado";
        case ORDENADO_INVERSAMENTE: return "ordenado-inversamente";
        case PARCIALMENTE_ORDENADO: return "parcialmente-ordenado";
        case REPETIDO: return "repetido";
        case DISTRIBUIDO: return "distribuido";
        default: return "desconhecido";
    }
}

// Obter o tipo de dados a partir do nome
TipoDados obterTipoPorNome(const std::string& nome) {
    static const std::unordered_map<std::string, TipoDados> mapa = {
        {"aleatorio", ALEATORIO},
        {"ordenado", ORDENADO},
        {"ordenado-inversamente", ORDENADO_INVERSAMENTE},
        {"parcialmente-ordenado", PARCIALMENTE_ORDENADO},
        {"repetido", REPETIDO},
        {"distribuido", DISTRIBUIDO}
    };
    
    auto it = mapa.find(nome);
    if (it != mapa.end()) {
        return it->second;
    }
    
    // Valor padrão
    return ALEATORIO;
}

// Obter nomes de todos os tipos disponíveis
std::vector<std::string> obterNomesTipos() {
    return {
        "aleatorio", "ordenado", "ordenado-inversamente", 
        "parcialmente-ordenado", "repetido", "distribuido"
    };
}

} // namespace gerador