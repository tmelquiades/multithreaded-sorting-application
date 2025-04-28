// gerador_dados.h
#ifndef GERADOR_DADOS_H
#define GERADOR_DADOS_H

#include <vector>
#include <string>

namespace gerador {

enum TipoDados {
    ALEATORIO,
    ORDENADO,
    ORDENADO_INVERSAMENTE,
    PARCIALMENTE_ORDENADO,
    REPETIDO,
    DISTRIBUIDO
};

std::vector<int> gerarDados(int tamanho, TipoDados tipo);
std::vector<int> lerArquivo(const std::string& caminho);
bool salvarArquivo(const std::vector<int>& dados, const std::string& caminho);
std::string obterNomeTipo(TipoDados tipo);
TipoDados obterTipoPorNome(const std::string& nome);
std::vector<std::string> obterNomesTipos();

} // namespace gerador

#endif // GERADOR_DADOS_H