// ordenacao_paralela.h
#ifndef ORDENACAO_PARALELA_H
#define ORDENACAO_PARALELA_H

#include <vector>
#include <string>
#include <functional>
#include "algoritmos_ordenacao.h"

namespace ordenacao_paralela {

// Estratégias de paralelização
void dividirTrabalho(std::vector<int>& arr, ordenacao::AlgoritmoOrdenacao algoritmo, int numThreads);
void paralelizarMergeSort(std::vector<int>& arr, int numThreads);
void paralelizarQuickSort(std::vector<int>& arr, int numThreads);

// Tipos para estratégias de paralelização
typedef std::function<void(std::vector<int>&, ordenacao::AlgoritmoOrdenacao, int)> EstrategiaParalela;
typedef std::function<void(std::vector<int>&, int)> EstrategiaParalelaEspecifica;

// Interface unificada
std::vector<std::string> obterNomesEstrategias();
EstrategiaParalela obterEstrategia(const std::string& nome);
EstrategiaParalelaEspecifica obterEstrategiaEspecifica(const std::string& nome);
bool ehEstrategiaEspecifica(const std::string& nome);

} // namespace ordenacao_paralela

#endif // ORDENACAO_PARALELA_H