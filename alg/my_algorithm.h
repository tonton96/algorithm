#ifndef ALGORITHM_MY_ALGORITHM_H
#define ALGORITHM_MY_ALGORITHM_H

#include "cstdint"
#include "vector"

/**
 * Finding the greatest common divisor of a, b
 */
int64_t find_gcd(int64_t a, int64_t b);

/**
 * Finding x, y, c with a*x + b*y = c, c = find_gcd(a, b), a > b > 0 (Extended Euclidean algorithm)
 */
void find_euclid_extended(int64_t a, int64_t b, int64_t &x, int64_t &y, int64_t &c);

/**
 * Finding x with ax = b (mod n), a > 0, 0 <= b, x < n (Linear congruence)
 */
std::vector<int64_t> find_linear_congruence(int64_t a, int64_t b, int64_t n);

/**
 * Calculating the combination k of n, 0 <= k <= n
 */
int64_t cal_ckn(int64_t k, int64_t n);

int64_t cal_large_ckn(int64_t k, int64_t n);

/**
 * Calculating the permutation k of n, 0 <= k <= n
 */
int64_t cal_akn(int64_t k, int64_t n);

#endif
