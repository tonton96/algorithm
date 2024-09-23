#ifndef ALGORITHM_HACKER_RANK_H
#define ALGORITHM_HACKER_RANK_H

#include "alg/my_algorithm.h"
#include "vector"
#include "cmath"
#include "string"

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

#if 0
// https://www.hackerrank.com/challenges/most-distant
double solve(std::vector<std::vector<int>> coordinates) {
    int max_x, max_y, min_x, min_y;
    bool fx = true, fy = true;
    for (auto &point: coordinates) {
        if (point[0] == 0 && point[1] == 0) {
            if (fx) {
                max_x = min_x = point[0];
                fx = false;
            } else {
                min_x = std::min(min_x, point[0]);
                max_x = std::max(max_x, point[0]);
            }
            if (fy) {
                max_y = min_y = point[1];
                fy = false;
            } else {
                min_y = std::min(min_y, point[1]);
                max_y = std::max(max_y, point[1]);
            }
        } else if (point[0] != 0) {
            if (fx) {
                max_x = min_x = point[0];
                fx = false;
            } else {
                min_x = std::min(min_x, point[0]);
                max_x = std::max(max_x, point[0]);
            }
        } else {
            if (fy) {
                max_y = min_y = point[1];
                fy = false;
            } else {
                min_y = std::min(min_y, point[1]);
                max_y = std::max(max_y, point[1]);
            }
        }
    }

    double m;
    if (!fx && !fy) {
        double dist[6];
        dist[0] = sqrt(1.0 * min_x * min_x + 1.0 * max_y * max_y);
        dist[1] = max_x - min_x;
        dist[2] = sqrt(1.0 * min_x * min_x + 1.0 * min_y * min_y);
        dist[3] = sqrt(1.0 * max_y * max_y + 1.0 * max_x * max_x);
        dist[4] = max_y - min_y;
        dist[5] = sqrt(1.0 * max_x * max_x + 1.0 * min_y * min_y);
        m = dist[0];
        for (int i = 1; i < 6; i++) {
            m = std::max(m, dist[i]);
        }
    } else if (!fx) {
        m = max_x - min_x;
    } else {
        m = max_x - min_y;
    }
    return m;
}
#endif

#if 0
// https://www.hackerrank.com/challenges/jim-and-the-jokes
long long solve(const vector<vector<int>> &lst_dates) {
    int dates[4][10][13];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 1; k <= 12; k++) {
                dates[i][j][k] = -1;
                if (i < k && j < k) {
                    dates[i][j][k] = i * k + j;
                }
            }
        }
    }

    int num_dates = (int) lst_dates.size();
    int counts[38];

    for (int &count: counts) {
        count = 0;
    }

    for (int i = 0; i < num_dates; i++) {
        int d = lst_dates[i][1];
        int m = lst_dates[i][0];
        int joke = dates[d / 10][d % 10][m];
        counts[joke]++;
    }

    long long count = 0;
    for (int &c: counts) {
        if (c >= 2) {
            count += c *(c-1)/2;
        }
    }
    return count;
}
#endif

#if 0
// https://www.hackerrank.com/challenges/possible-path
std::string solve(long a, long b, long x, long y) {
    if(find_gcd(a, b) == find_gcd(x, y)){
        return "YES";
    }
    return "NO";
}
#endif

#if 0
// https://www.hackerrank.com/challenges/mutual-recurrences
const uint64_t MAX = 1000000000000000000;
const uint64_t N = 1000000000;
std::map<uint64_t, uint64_t> fib_map;

// Returns n'th fibonacci number using table fib_map
uint64_t find_fib(uint64_t n) {
    if (n == 0)
        return 0;
    if (n == 1 || n == 2) {
        return 1;
    }
    if (fib_map.count(n)) {
        return fib_map[n];
    }

    uint64_t k = (n & 1) ? (n + 1) / 2 : n / 2;

    fib_map[n] = (n & 1) ? (find_fib(k) * find_fib(k) + find_fib(k - 1) * find_fib(k - 1)) :
                 (2 * find_fib(k - 1) + find_fib(k)) * find_fib(k);
    fib_map[n] = fib_map[n] % N;
    return fib_map[n];
}

#define MOD 1000000000
vector<int> solve(int a, int b, int c, int d, int e, int f, int g, int h, long n) {
    int64_t x[10], y[10], dn = 1, hn = 1, xn, yn;
    int64_t xna, ynb, ync, yne, xnf, xng;

    for (int nn = 0; nn < 10; nn++) {
        xna = nn - a >= 0 ? x[nn - a] : 1;
        ynb = nn - b >= 0 ? y[nn - b] : 1;
        ync = nn - c >= 0 ? y[nn - c] : 1;
        yne = nn - e >= 0 ? y[nn - e] : 1;
        xnf = nn - f >= 0 ? x[nn - f] : 1;
        xng = nn - g >= 0 ? x[nn - g] : 1;

        x[nn] = (xna + ynb + ync + nn * dn) % MOD;
        y[nn] = (yne + xnf + xng + nn * hn) % MOD;
        dn = (dn * d) % MOD;
        hn = (hn * h) % MOD;
    }

    for (int64_t nn = 10; nn <= n; nn++) {
        xn = (x[10 - a] + y[10 - b] + y[10 - c] + nn * dn) % MOD;
        yn = (y[10 - e] + x[10 - f] + x[10 - g] + nn * hn) % MOD;
        dn = (dn * d) % MOD;
        hn = (hn * h) % MOD;
        for (int i = 0; i < 9; i++) {
            x[i] = x[i + 1];
            y[i] = y[i + 1];
        }
        x[9] = xn;
        y[9] = yn;
    }

    return {(int) xn, (int) yn};
}
#endif

#if 0
// https://www.hackerrank.com/challenges/constructing-a-number
string canConstruct(vector<int> a) {
    int sum = 0;
    for (auto x: a) {
        int s = x;
        while (s > 0) {
            sum += s % 10;
            s = s / 10;
        }
    }
    if (sum % 3 == 0) {
        return "YES";
    }
    return "NO";
}
#endif

#if 0
int closestNumber(int a, int b, int x) {
    auto r = pow(a, b) / x;
    return (int) (round(r) * x);
}
#endif

#endif //ALGORITHM_HACKER_RANK_H
