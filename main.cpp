#include <iostream>
#include "algorithm"
#include "alg/algorithm.h"

int solve(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        return std::abs(y2 - y1) - 1;
    }
    if (y2 == y1) {
        return std::abs(x2 - x1) - 1;
    }

    int a = std::abs(y2 - y1);
    int b = std::abs(x2 - x1);
    int c = find_gcd(a, b);
    a = a / c;

    int delta = std::abs(y2 - y1);
    if (delta % a == 0) {
        return delta / a - 1;
    }
    return delta / a;
}

int main() {
    int x1 = 0, y1 = 2, x2 = 4, y2 = 0;
    int c = solve(x1, y1, x2, y2);
    return 0;
}
