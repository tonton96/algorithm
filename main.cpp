#include <iostream>
#include "algorithm"
#include "cmath"
#include "map"
#include "alg/my_algorithm.h"
#include "sstream"

using namespace std;
using namespace alg;

int getValue(int x, int y, vector<vector<int>> &M)
{
    if (M[x][y] == -1)
    {
        bool flag = true;
        if (x - 2 >= 0 && y + 1 < 16)
        {
            flag = flag && getValue(x - 2, y + 1, M) == 0;
        }
        if (x - 2 >= 0 && y - 1 >= 0)
        {
            flag = flag && getValue(x - 2, y - 1, M) == 0;
        }
        if (x + 1 < 16 && y - 2 >= 0)
        {
            flag = flag && getValue(x + 1, y - 2, M) == 0;
        }
        if (x - 1 >= 0 && y - 2 >= 0)
        {
            flag = flag && getValue(x - 1, y - 2, M) == 0;
        }
        if (flag)
        {
            M[x][y] = 1;
        }
        else
        {
            M[x][y] = 0;
        }
    }
    return M[x][y];
}

string chessboardGame(int x, int y)
{
    x--;
    y--;
    vector<vector<int>> M(16);
    for (auto &m : M)
    {
        m.resize(16);
    }
    for (int i = 0; i < 16; i++)
    {
        M[i][0] = M[0][i] = 1;
    }
    for (int i = 1; i < 16; i++)
    {
        for (int j = 1; j < 16; j++)
        {
            M[i][j] = -1;
        }
    }

    auto val = getValue(x, y, M);
    std::cout << val;
    if (val == 1)
    {
        return "Second";
    }
    return "First";
}

int calMedian2(const vector<int> &x, int id, int len)
{
    vector<int> y(x.data() + id, x.data() + id + len);
    sort(y.begin(), y.end());
    return (len % 2 == 1) ? (2 * y[len / 2]) : (y[len / 2] + y[len / 2 - 1]);
}

int main()
{
    std::string str = "( 2 * 3 + 7 / 8 ) * ( 5 - 1 )";
    auto val = calPostfix(infix2Postfix(str));
    return 0;
}
