#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"
#include "map"
#include "list"

namespace test2_p165
{
    void init(const std::string &s1, const std::string &s2, std::vector<std::vector<int>> &table)
    {
        auto num_rows = s1.size();
        auto num_cols = s2.size();

        table.resize(num_rows);
        for (auto &r : table)
        {
            r.resize(num_cols);
        }

        for (int i = 0; i < num_cols; i++)
        {
            if (s1[0] == s2[i])
            {

                for (int j = i; j < num_cols; j++)
                {
                    table[0][j] = 1;
                }
                break;
            }
        }
        for (int i = 0; i < num_rows; i++)
        {
            if (s2[0] == s1[i])
            {

                for (int j = i; j < num_rows; j++)
                {
                    table[j][0] = 1;
                }
                break;
            }
        }
    }

    std::string trace(const std::string &s1, const std::string &s2, std::vector<std::vector<int>> &table)
    {
        std::string result;
        int num_rows = s1.size(), num_cols = s2.size();
        result.reserve(std::max(num_rows, num_cols));
        int r = num_rows - 1, c = num_cols - 1;
        while (true)
        {
            if (s1[r] == s2[c])
            {
                result.push_back(s1[r]);
                r--;
                c--;
            }
            else
            {
                if (table[r][c] == table[r - 1][c - 1])
                {
                    r--;
                    c--;
                }
                else if (table[r][c] == table[r - 1][c])
                {
                    r--;
                }
                else
                {
                    c--;
                }
            }

            if (r < 0 || c < 0)
            {
                break;
            }
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    std::string handler(const std::string &s1, const std::string &s2)
    {
        std::vector<std::vector<int>> table;
        init(s1, s2, table);

        int num_rows = s1.size(), num_cols = s2.size();
        for (int r = 1; r < num_rows; r++)
        {
            for (int c = 1; c < num_cols; c++)
            {
                if (s1[r] == s2[c])
                {
                    table[r][c] = table[r - 1][c - 1] + 1;
                }
                else
                {
                    table[r][c] = std::max(table[r - 1][c - 1], std::max(table[r][c - 1], table[r - 1][c]));
                }
            }
        }

        return trace(s1, s2, table);
    }

    void test()
    {
        std::string s1 = "abcdefghi123";
        std::string s2 = "abc1def2ghi3";
        std::cout << "Output: " << handler(s1, s2);
    }
}

namespace test3_p165
{
    const int MAX_SIXE = 128;

    int table[MAX_SIXE][MAX_SIXE];

    std::string trace(const std::string &input)
    {
        std::string output;
        output.resize(input.size() + table[0][input.size() - 1]);

        int from = 0, to = output.size() - 1;
        int i = 0, j = input.size() - 1;
        while (true)
        {
            if (i == j)
            {
                output[from] = output[to] = input[i];
                break;
            }
            if (i > j)
            {
                break;
            }
            if (input[i] == input[j])
            {
                output[from] = output[to] = input[i];
                from++;
                to--;
                i++;
                j--;
            }
            else
            {
                if (table[i][j] == table[i + 1][j] + 1)
                {
                    output[from++] = input[i];
                    output[to--] = input[i];
                    i++;
                }
                else
                {
                    output[from++] = input[j];
                    output[to--] = input[j];
                    j--;
                }
            }
        }

        return output;
    }

    void init(int size)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                table[i][j] = 0;
            }
        }
    }

    std::string handler(const std::string &input)
    {
        int size = input.size();
        init(size);

        for (int j = 1; j < size; j++)
        {
            for (int i = 0; i < size - j; i++)
            {
                int from = i;
                int to = j + i;
                if (input[from] == input[to])
                {
                    table[from][to] = table[from + 1][to - 1];
                }
                else
                {
                    table[from][to] = std::min(table[from + 1][to], table[from][to - 1]) + 1;
                }
            }
        }

        return trace(input);
    }

    void test()
    {
        std::string S = "edbabcd";
        std::string T = handler(S);
        std::cout << "Output: " << T << std::endl;
    }
}
