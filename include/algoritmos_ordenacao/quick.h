// quick.h
#pragma once
#include <vector>

namespace ordenacao {
    void quickSort(std::vector<int>& arr, int low, int high);
    void quickSortWrapper(std::vector<int>& arr);
    int particionar(std::vector<int>& arr, int low, int high);
} // namespace ordenacao