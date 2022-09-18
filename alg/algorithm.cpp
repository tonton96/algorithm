#include "algorithm.h"

long find_gcd(long a, long b) {
    if (a < b) {
        long c = a;
        a = b;
        b = c;
    }

    while (b != 0) {
        long r = a % b;
        a = b;
        b = r;
    }

    return a;
}

void find_euclid_extended(long a, long b, long &x, long &y, long &c) {
    long x0 = 1, y0 = 0, x1 = 0, y1 = 1;
    while (b > 0) {
        long r = a % b;
        if (r == 0)
            break;
        long q = a / b;
        x = x0 - q * x1;
        y = y0 - q * y1;
        a = b;
        b = r;
        x0 = x1;
        y0 = y1;
        x1 = x;
        y1 = y;
    }
    x = x1;
    y = y1;
    c = b;
}

std::vector<long> find_linear_congruence(long a, long b, long n) {
    a = a % n;
    long v, u, d;
    find_euclid_extended(n, a, v, u, d);
    if (b % d != 0) {
        return {};
    }
    long x0 = (u * (b / d)) % n;
    std::vector<long> r;
    for (int i = 0; i < d; i++) {
        r.push_back((x0 + i * n / d) % n);
    }
    return r;
}

long cal_ckn(long k, long n) {
    long t = 1, m = 1;
    for (long i = k + 1; i <= n; i++) {
        t *= i;
    }
    for (long i = 2; i <= n - k; i++) {
        m *= i;
    }
    return t / m;
}

long cal_akn(long k, long n) {
    long a = 1;
    for (long i = n - k + 1; i <= n; i++) {
        a *= i;
    }
    return a;
}