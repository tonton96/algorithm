#ifndef ALGORITHM_ALGORITHM_H
#define ALGORITHM_ALGORITHM_H

#include "vector"

/**
 * Finding the greatest common divisor of a, b
 */
long find_gcd(long a, long b);

/**
 * Finding x, y, c with a*x + b*y = c, c = find_gcd(a, b), a > b > 0 (Extended Euclidean algorithm)
 */
void find_euclid_extended(long a, long b, long &x, long &y, long &c);

/**
 * Finding x with ax = b (mod n), a > 0, 0 <= b, x < n (Linear congruence)
 */
std::vector<long> find_linear_congruence(long a, long b, long n);

/**
 * Calculating the combination k of n, 0 <= k <= n
 */
long cal_ckn(long k, long n);

/**
 * Calculating the permutation k of n, 0 <= k <= n
 */
long cal_akn(long k, long n);

#endif
