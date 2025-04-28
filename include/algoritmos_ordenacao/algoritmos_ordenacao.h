// algoritmos_ordenacao.h
#ifndef ALGORITMOS_ORDENACAO_H
#define ALGORITMOS_ORDENACAO_H

#include <vector>
#include <functional>
#include <string>

namespace ordenacao {

// Invólucros para uniformizar chamadas de algoritmos
typedef std::function<void(std::vector<int>&)> AlgoritmoOrdenacao;

// Mapeamento de nomes para funções de ordenação
std::vector<std::string> obterNomesAlgoritmos();
AlgoritmoOrdenacao obterAlgoritmo(const std::string& nome);

} // namespace ordenacao

#endif // ALGORITMOS_ORDENACAO_H
