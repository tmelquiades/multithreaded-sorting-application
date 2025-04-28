// radix.h
#pragma once
#include <vector>

namespace ordenacao {
    void radixSort(std::vector<int>& arr);
    void countingSortForRadix(std::vector<int>& arr, int pos_decimal);
} // namespace ordenacao