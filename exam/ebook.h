#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"

namespace test2_p165
{

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
        std::string S = "abcdefg_hh_gfe_1_d_2_c_3_ba";
        std::string T = handler(S);
        std::cout << "Output T: " << T << std::endl;
    }
}
