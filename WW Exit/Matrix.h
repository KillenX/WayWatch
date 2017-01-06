#pragma once
#include <vector>

// use symmetric matrix instead? (with real memory usage of bottom triangle or upper triangle)
template <typename T>
using Matrix = std::vector<std::vector<T>>;