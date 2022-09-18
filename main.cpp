#include <iostream>
#include "algorithm"
#include "alg/algorithm.h"

int main() {
    std::vector<int> x = {1, 2, 3};
    auto y = std::max_element(x.begin(), x.end());
    return 0;
}
