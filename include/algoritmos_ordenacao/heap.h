// heap.h
#pragma once
#include <vector>

namespace ordenacao {
    void heapSort(std::vector<int>& arr);
    void buildMaxHeap(std::vector<int>& arr);
    void heapify(std::vector<int>& arr, int n, int i);
} // namespace ordenacao