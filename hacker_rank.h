#ifndef ALGORITHM_HACKER_RANK_H
#define ALGORITHM_HACKER_RANK_H

#include "alg/algorithm.h"
#include "vector"
#include "cmath"

#if 0
//https://www.hackerrank.com/challenges/harry-potter-and-the-floating-rocks/problem
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
#endif

#if 0
//https://www.hackerrank.com/challenges/russian-peasant-exponentiation
void get_complex_mod(long a, long b, long k, int long n, long &c, long &d) {
    if (k == 0) {
        c = 1;
        d = 0;
        return;
    }
    if (k == 1) {
        c = a % n;
        d = b % n;
        return;
    }
    if (k % 2 == 0) {
        long cc, dd;
        get_complex_mod(a, b, k / 2, n, cc, dd);
        c = (cc * cc - dd * dd) % n;
        d = (2 * cc * dd) % n;
        return;
    } else {
        long cc, dd;
        get_complex_mod(a, b, k - 1, n, cc, dd);
        c = (cc * a - dd * b) % n;
        d = (cc * b + dd * a) % n;
        return;
    }
}

std::vector<int> solve(int a, int b, long k, int m) {
    long c, d;
    get_complex_mod(a, b, k, m, c, d);
    if (c < 0) {
        c += m;
    }
    if (d < 0) {
        d += m;
    }
    return {(int) c, (int) d};
}
#endif

#endif //ALGORITHM_HACKER_RANK_H
