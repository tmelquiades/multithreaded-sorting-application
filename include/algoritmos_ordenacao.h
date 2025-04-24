// algoritmos_ordenacao.h
#ifndef ALGORITMOS_ORDENACAO_H
#define ALGORITMOS_ORDENACAO_H

#include <vector>
#include <functional>
#include <string>

namespace ordenacao {

// Algoritmos de ordenação sequenciais
void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void selectionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int low, int high);
void mergeSort(std::vector<int>& arr, int left, int right);
void heapSort(std::vector<int>& arr);
void countingSort(std::vector<int>& arr);
void radixSort(std::vector<int>& arr);

// Invólucros para uniformizar chamadas de algoritmos
typedef std::function<void(std::vector<int>&)> AlgoritmoOrdenacao;

// Mapeamento de nomes para funções de ordenação
std::vector<std::string> obterNomesAlgoritmos();
AlgoritmoOrdenacao obterAlgoritmo(const std::string& nome);

} // namespace ordenacao

#endif // ALGORITMOS_ORDENACAO_H
