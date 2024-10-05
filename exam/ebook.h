#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"
#include "map"
#include "list"

namespace test1_150
{
    std::string convert(const std::string &str)
    {
        std::map<char, int> cost;
        cost['*'] = 2;
        cost['+'] = 1;
        cost['('] = cost[')'] = 0;

        std::string re;
        std::string stack;
        re.reserve(str.size());
        stack.reserve(str.size());

        for (auto &c : str)
        {
            switch (c)
            {
            case '+':
            case '*':

                while (!stack.empty())
                {
                    auto val = stack[stack.size() - 1];
                    if (cost[val] >= cost[c])
                    {
                        re.push_back(c);
                        stack.pop_back();
                    }
                    else
                    {
                        break;
                    }
                }
                stack.push_back(c);
                break;
            case '(':
                stack.push_back(c);
                break;
            case ')':
                while (!stack.empty())
                {
                    char val = stack[stack.size() - 1];
                    stack.pop_back();
                    if (val != '(')
                    {
                        re.push_back(val);
                    }
                    else
                    {
                        break;
                    }
                }
                break;
            case ' ':
                break;
            default:
                re.push_back(c);
                break;
            }
        }
        while (!stack.empty())
        {
            re.push_back(stack[stack.size() - 1]);
            stack.pop_back();
        }

        return re;
    }

    // Solution 1
    int calTime(const std::string &str, int p, int q)
    {
        auto cvt_str = convert(str);

        std::vector<int> stack;
        stack.reserve(cvt_str.size());

        int val = 0;
        for (auto &c : cvt_str)
        {
            if (c == '+')
            {
                int val1 = stack.back();
                stack.pop_back();
                int val2 = stack.back();
                stack.pop_back();

                val = p + std::max(val1, val2);
                stack.push_back(val);
            }
            else if (c == '*')
            {
                int val1 = stack.back();
                stack.pop_back();
                int val2 = stack.back();
                stack.pop_back();

                val = q + std::max(val1, val2);
                stack.push_back(val);
            }
            else
            {
                stack.push_back(0);
            }
        }

        return val;
    }

    // Solution 2
    int calTime2(const std::string &str, int from, int to, int p, int q)
    {
        if (to == from)
        {
            return 0;
        }

        else
        {
            int from1, to1, from2, to2;
            from1 = to1 = from;
            int val = 0;
            while (true)
            {
                if (str[to1] == '(')
                {
                    val++;
                }
                else if (str[to1] == ')')
                {
                    val--;
                }
                if (val == 0)
                {
                    break;
                }
                to1++;
            }
            from2 = to2 = to;
            while (true)
            {
                if (str[from2] == '(')
                {
                    val++;
                }
                else if (str[from2] == ')')
                {
                    val--;
                }
                if (val == 0)
                {
                    break;
                }
                from2--;
            }

            if (from1 == from2 && to1 == to2)
            {
                return calTime2(str, from1 + 1, to1 - 1, p, q);
            }

            if (str[to1 + 1] == '+')
            {
                return std::max(calTime2(str, from1, to1, p, q), calTime2(str, from2, to2, p, q)) + p;
            }
            else if (str[to1 + 1] == '*')
            {
                return std::max(calTime2(str, from1, to1, p, q), calTime2(str, from2, to2, p, q)) + q;
            }
        }
        return 0;
    }

    // Solution 3
    struct Node{
        char val = 0;
        int cost = 0;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    void convert(const std::string&str, int p, int q, std::vector<Node> &tree){
        std::string stack, postfix;
        stack.reserve(str.size());
        postfix.reserve(str.size());        

        std::map<char, int> cost;
        cost['*'] = cost['+'] = 1;
        cost['('] = cost[')'] = 0;

        for (auto &c : str)
        {
            switch (c)
            {
            case '(':
                stack.push_back(c);
                break;
            case ')':
                while(!stack.empty()){
                    auto i = stack.back();
                    stack.pop_back();
                    if(i == '('){
                        break;
                    }
                    else{
                        postfix.push_back(i);
                    }
                }
                break;
            case '+':
            case '*':
                while (!stack.empty())
                {
                    auto i = stack.back();
                    if (cost[i] >= cost[c])
                    {
                        postfix.push_back(i);
                        stack.pop_back();
                    }
                    else{
                        break;
                    }
                }
                stack.push_back(c);
                break;
            default:
                postfix.push_back(c);
                break;
            }
        }
        while (!stack.empty())
        {
            postfix.push_back(stack.back());
            stack.pop_back();
        }

        tree.resize(postfix.size());
        std::vector<Node *> stack_node;
        stack_node.reserve(postfix.size());

        for (int i = 0; i < postfix.size(); i++)
        {
            auto &c = postfix[i];
            auto &node = tree[i];
            
            switch (c)
            {
            case '*':
            case '+':
                node.val = c;
                node.right = stack_node.back();
                stack_node.pop_back();
                node.left = stack_node.back();
                stack_node.pop_back();
                node.left->parent = &node;
                node.right->parent = &node;
                node.cost = std::max(node.left->cost, node.right->cost) + (c == '+' ? p : q);
                node.parent = nullptr;
                break;
            default:
                node.val = c;
                node.cost = 0;
                node.left = nullptr;
                node.right = nullptr;     
                node.parent = nullptr;
                break;
            }

            stack_node.push_back(&node);
        }
    }

    void handler(const std::string &str, int p, int q){
        std::vector<Node> tree;
        convert(str, p, q, tree);

        auto cost = tree.back().cost;
        std::cout << cost << std::endl; // [1]

        std::string minStr;
        std::cout << minStr; //[2]
    }

    void test()
    {

        // std::string str = "a+(a+(a+(a+(a+(a+(a+a))))))";
        // std::string str = "(((a+(b+(c+d)))*e)*f)";
        std::string str = "(((((a*b)*c)*d)+e)+(f*g))";
        // auto t = handler(str, 0, str.size() - 1, 1, 1);
        handler(str, 1, 1);
        std::cout << str;
    }
}

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
