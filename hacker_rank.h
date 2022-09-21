#ifndef ALGORITHM_HACKER_RANK_H
#define ALGORITHM_HACKER_RANK_H

#include "alg/my_algorithm.h"
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
int64_t solve(const std::vector<std::vector<int>> &lst_dates) {
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

    int64_t count = 0;
    for (int &c: counts) {
        if (c >= 2) {
            count += cal_large_ckn(2, c);
        }
    }
    return count;
}
#endif

#endif //ALGORITHM_HACKER_RANK_H
