// heap.h
#pragma once
#include <vector>

namespace ordenacao {
    void mergeSort(std::vector<int>& arr, int esquerda, int direita);
    void mergeSortWrapper(std::vector<int>& arr);
    void merge(std::vector<int>& arr, int inicio, int meio, int fim);
} // namespace ordenacao