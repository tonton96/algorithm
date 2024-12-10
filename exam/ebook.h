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
    struct Node
    {
        char val = 0;
        int cost = 0;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    void convert(const std::string &str, int p, int q, std::vector<Node> &tree)
    {
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
                while (!stack.empty())
                {
                    auto i = stack.back();
                    stack.pop_back();
                    if (i == '(')
                    {
                        break;
                    }
                    else
                    {
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
                    else
                    {
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

    void findStr(const Node *node, std::string &str)
    {
        if ((node->left == nullptr) && (node->right == nullptr))
        {
            str.push_back(node->val);
        }
        else
        {
            str.push_back('(');
            if (node->left != nullptr)
            {
                findStr(node->left, str);
            }

            str.push_back(node->val);

            if (node->right != nullptr)
            {
                findStr(node->right, str);
            }

            str.push_back(')');
        }
    }

    void recalc(Node *node, int p, int q)
    {
        while (true)
        {
            node->cost = std::max(node->left->cost, node->right->cost);
            node->cost += (node->val == '+') ? p : q;
            if (node->parent == nullptr)
            {
                break;
            }
            node = node->parent;
        }
    }

    void handler(const std::string &str, int p, int q)
    {
        std::vector<Node> tree;
        convert(str, p, q, tree);
        const auto cost = tree.back().cost;

        while (true)
        {
            bool found = false;
            for (auto &node : tree)
            {
                if (node.val != '*' && node.val != '+')
                {
                    continue;
                }

                if (node.left->val == node.val)
                {
                    auto n1 = node.left->left;
                    auto n2 = node.left->right;
                    auto n3 = node.right;

                    if (n1->cost >= n2->cost && n1->cost > n3->cost)
                    {
                        node.right = n1;
                        node.left->left = n3;
                        recalc(node.left, p, q);
                        found = true;
                        break;
                    }

                    if (n2->cost >= n1->cost && n2->cost > n3->cost)
                    {
                        node.right = n2;
                        node.left->right = n3;
                        recalc(node.left, p, q);
                        found = true;
                        break;
                    }
                }
                else if (node.right->val == node.val)
                {
                    auto n1 = node.right->left;
                    auto n2 = node.right->right;
                    auto n3 = node.left;

                    if (n1->cost >= n2->cost && n1->cost > n3->cost)
                    {
                        node.left = n1;
                        node.right->left = n3;
                        recalc(node.right, p, q);
                        found = true;
                        break;
                    }

                    if (n2->cost >= n1->cost && n2->cost > n3->cost)
                    {
                        node.left = n2;
                        node.right->right = n3;
                        recalc(node.right, p, q);
                        found = true;
                        break;
                    }
                }

                if (node.left->val == node.val && node.right->val == node.val)
                {
                    auto n1 = node.left->left;
                    auto n2 = node.left->right;
                    auto n3 = node.right->left;
                    auto n4 = node.right->right;
                    if (n1->cost > n2->cost)
                    {
                        auto tg = n1;
                        n1 = n2;
                        n2 = tg;
                    }
                    if (n3->cost > n4->cost)
                    {
                        auto tg = n3;
                        n3 = n4;
                        n4 = n3;
                    }

                    if (n1->cost < n3->cost && n4->cost > n2->cost)
                    {
                        node.left->left = n1;
                        node.left->right = n4;
                        node.right->left = n2;
                        node.right->right = n3;
                        recalc(&node, p, q);
                        found = true;
                        break;
                    }

                    if (n2->cost > n4->cost && n3->cost < n1->cost)
                    {
                        node.left->left = n3;
                        node.left->right = n2;
                        node.right->left = n1;
                        node.right->right = n4;
                        recalc(&node, p, q);
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
            {
                break;
            }
        }

        std::string minStr;
        auto min_cost = tree.back().cost;
        findStr(&tree.back(), minStr);

        std::cout << cost << std::endl;     // Line 1
        std::cout << minStr << std::endl;   // Line 2
        std::cout << min_cost << std::endl; // Line 3
    }

    void test()
    {

        // std::string str = "a+(a+(a+(a+(a+(a+(a+a))))))";
        // std::string str = "(((a+(b+(c+d)))*e)*f)";
        std::string str = "(((((a*b)*c)*d)+e)+(f*g))";
        int p = 1, q = 1;
        handler(str, p, q);
    }
}

namespace test2_150
{
    const int MAX_VAL = 50;
    int primes[MAX_VAL + 1];
    int table1[MAX_VAL + 1][MAX_VAL + 1]; // table1[i][j]: so phan tu toi da (primes[0 - i]) co tong = j
    int table2[MAX_VAL + 1];              // Tinh B
    int num_primes = 0;

    bool checkPrime(int val)
    {
        if (val < 2)
        {
            return false;
        }
        for (int i = 2; i < val; i++)
        {
            if (val % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    void findTable()
    {
        num_primes = 0;
        for (int i = 0; i <= MAX_VAL; i++)
        {
            if (checkPrime(i))
            {
                primes[num_primes++] = i;
            }
        }

        for (int r = 0; r < num_primes; r++)
        {
            for (int c = 0; c <= MAX_VAL; c++)
            {
                table1[r][c] = 0;
            }
        }

        for (int i = 0; i < num_primes; i++)
        {
            table1[i][0] = table1[i][1] = 0;
            table1[i][2] = 1;
        }

        for (int r = 1; r < num_primes; r++)
        {
            for (int c = 3; c <= MAX_VAL; c++)
            {
                table1[r][c] = table1[r - 1][c];
                if (c > primes[r])
                {
                    if (table1[r - 1][c - primes[r]] > 0)
                    {
                        table1[r][c] = std::max(1 + table1[r - 1][c - primes[r]], table1[r][c]);
                    }
                }
                else if (c == primes[r])
                {
                    table1[r][c] = std::max(1, table1[r][c]);
                }
            }
        }

        for (int n = 0; n <= MAX_VAL; n++)
        {
            table2[n] = table1[num_primes - 1][n];
            for (int i = 0; i < num_primes; i++)
            {
                if (n >= primes[i])
                {
                    if (table1[num_primes - 1][n - primes[i]] > 0)
                    {
                        table2[n] = std::max(table2[n], 1 + table1[num_primes - 1][n - primes[i]]);
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    int getVal(int a)
    {
        return table2[a];
    }

    void test()
    {
        findTable();

        // Get A
        const int N = 2, M = 3;
        int A[N][M] = {{10, 12, 11},
                       {8, 3, 7}};

        // Calc B -> print OUT1
        int B[N][M]{};
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                B[i][j] = getVal(A[i][j]);
                std::cout << B[i][j] << " ";
            }
            std::cout << std::endl;
        }

        int max_r = 0, max_c = 0, max_s = 1, max_dr = 1, max_dc = 1;
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < M; c++)
            {
                int dc = 1, dr = 1;
                while (r + dr < N)
                {
                    if (B[r][c] != B[r + dr][c])
                    {
                        break;
                    }
                    dr++;
                }
                while (c + dc < M)
                {
                    if (B[r][c] != B[r][c + dc])
                    {
                        break;
                    }
                    dc++;
                }

                if (dc * dr > max_s)
                {
                    max_s = dc * dr;
                    max_dc = dc;
                    max_dr = dr;
                    max_r = r;
                    max_c = c;
                }
            }
        }

        // Print OUT2
        std::cout << max_s << " " << max_r << " " << max_c << " " << max_r + max_dr - 1
                  << " " << max_c + max_dc - 1 << std::endl;
    }
}

namespace test3_150
{
    const int INF = 1e9, UNASSIGN = -1;

    // Dijkstra algorithm
    void find_path(const std::vector<std::vector<int>> &cost, int start, int stop,
                   std::vector<int> &min_path, int &len_path)
    {
        int num_points = cost.size();
        std::vector<bool> free(num_points, true);
        std::vector<int> dist(num_points, INF);
        std::vector<int> trace(num_points, UNASSIGN);

        dist[start] = 0;
        while (true)
        {
            int min_dist = INF, min_point = UNASSIGN;
            for (int point = 0; point < num_points; point++)
            {
                if (free[point])
                {
                    if (dist[point] < min_dist)
                    {
                        min_dist = dist[point];
                        min_point = point;
                    }
                }
            }

            if (min_point == UNASSIGN)
            {
                break;
            }

            free[min_point] = false;
            if (min_point == stop)
            {
                break;
            }

            for (int point = 0; point < num_points; point++)
            {
                if (free[point] && (dist[point] > dist[min_point] + cost[min_point][point]))
                {
                    dist[point] = dist[min_point] + cost[min_point][point];
                    trace[point] = min_point;
                }
            }
        }

        min_path.clear();
        len_path = INF;
        if (!free[stop])
        {
            len_path = dist[stop];
            min_path.reserve(num_points);

            int point = stop;
            while (true)
            {
                min_path.push_back(point);
                if (point == start)
                {
                    break;
                }
                point = trace[point];
            }
        }
        std::reverse(min_path.begin(), min_path.end());
    }

    int min_path(const std::vector<std::string> &map, int fr, int fc, int tr, int tc)
    {
        const char wall = '#';
        int num_rows = map.size();
        int num_cols = map.empty() ? 0 : map[0].size();
        int total_points = num_rows * num_cols;

        if (fr < 0 || fr >= num_rows || fc < 0 || fc >= num_cols)
        {
            return INF;
        }

        if (tr < 0 || tr >= num_rows || tc < 0 || tc >= num_cols)
        {
            return INF;
        }

        if (map[fr][fc] == wall || map[tr][tc] == wall)
        {
            return INF;
        }

        static std::vector<vector<bool>> visited;
        visited.resize(num_rows);
        for (auto &i : visited)
        {
            i.resize(num_cols);
            for (auto &j : i)
                j = false;
        }

        static std::vector<std::vector<int>> cost;
        cost.resize(num_rows);
        for (auto &i : cost)
        {
            i.resize(num_cols);
            for (auto &j : i)
                j = INF;
        }

        std::vector<int> queue;
        queue.resize(num_cols * num_rows);

        int start_queue = 0, end_queue = 1;
        queue[start_queue] = fr * num_cols + fc;
        cost[fr][fc] = 0;
        visited[fr][fc] = true;

        const int delta[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (end_queue > start_queue)
        {
            int r = queue[start_queue] / num_cols;
            int c = queue[start_queue] % num_cols;
            start_queue++;

            for (int i = 0; i < 4; i++)
            {
                int nr = r + delta[i][0];
                int nc = c + delta[i][1];
                if (nr >= 0 && nr < num_rows && nc >= 0 && nc < num_cols)
                {
                    if (map[nr][nc] != wall && !visited[nr][nc])
                    {
                        queue[end_queue] = nr * num_cols + nc;
                        end_queue++;
                        cost[nr][nc] = cost[r][c] + 1;
                        visited[nr][nc] = true;
                    }
                }
            }

            if(cost[tr][tc] != INF){
                break;
            }
        }

        return cost[tr][tc];
    }

    void map2cost(std::vector<std::string> map, std::vector<std::vector<int>> &cost)
    {
        int num_rows = map.size();
        int num_cols = map.empty() ? 0 : map[0].size();
        int total_points = 4 * num_rows * num_cols;
        cost.resize(total_points);
        for (auto &i : cost)
        {
            i.resize(total_points, INF);
        }

        const char space = '.', wall ='#';
        const int delta[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (int r = 0; r < num_rows; r++)
        {
            for (int c = 0; c < num_cols; c++)
            {
                if (map[r][c] != wall)
                {
                    for (int h = 0; h < 4; h++)
                    {
                        int pr = r + delta[h][0];
                        int pc = c + delta[h][1];
                        if (pr >= 0 && pr < num_rows && pc >= 0 && pc < num_cols)
                        {
                            if (map[pr][pc] != wall)
                            {
                                auto val = map[r][c];
                                map[r][c] = wall;

                                for (int i = 0; i < 4; i++)
                                {
                                    int nr = r + delta[i][0];
                                    int nc = c + delta[i][1];
                                    if (nr >= 0 && nr < num_rows && nc >= 0 && nc < num_cols)
                                    {
                                        int rr = r - delta[i][0];
                                        int cc = c - delta[i][1];
                                        if (rr >= 0 && rr < num_rows && cc >= 0 && cc < num_cols)
                                        {
                                            auto val = min_path(map, pr, pc, nr, nc) + 1;
                                            cost[h * num_cols * num_rows + r * num_cols + c][i * num_cols * num_rows + rr * num_cols + cc] = val;
                                        }
                                    }
                                }

                                map[r][c] = val;
                            }
                        }
                    }
                }
            }
        }
    }

    void handler(std::vector<std::string> map)
    {
        int num_rows = map.size();
        int num_cols = map.empty() ? 0 : map[0].size();

        std::vector<std::vector<int>> cost;
        map2cost(map, cost);

        const char start = '$', stop = '@', star = '*', wall = '#';
        int start_r, start_c, stop_r, stop_c, star_r, star_c;
        for (int r = 0; r < num_rows; r++)
        {
            for (int c = 0; c < num_cols; c++)
            {
                if (map[r][c] == start)
                {
                    start_r = r;
                    start_c = c;
                }
                else if (map[r][c] == stop)
                {
                    stop_r = r;
                    stop_c = c;
                }
                else if (map[r][c] == star)
                {
                    star_r = r;
                    star_c = c;
                }
            }
        }

        const int delta[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int len[4];
        auto tmp = map[start_r][start_c];
        map[start_r][start_c] = wall;
        for (int i = 0; i < 4; i++)
        {
            len[i] = min_path(map, star_r, star_c, start_r + delta[i][0], start_c + delta[i][1]);
        }
        map[start_r][start_c] = tmp;

        int len_path_ = INF;
        std::vector<int> min_path_;
        for (int i = 0; i < 4; i++)
        {
            int start = i * num_cols * num_rows + start_r * num_cols + start_c;
            for (int j = 0; j < 4; j++)
            {
                int stop = j * num_cols * num_rows + stop_r * num_cols + stop_c;
                int len_path;
                std::vector<int> min_path;
                find_path(cost, start, stop, min_path, len_path);
                len_path += len[i];

                if (len_path < len_path_)
                {
                    len_path_ = len_path;
                    min_path_ = min_path;
                }
            }
        }
        for (auto val : min_path_)
        {
            int h = val / (num_cols * num_rows);
            int r = (val - h * num_cols * num_rows) / num_cols;
            int c = (val - h * num_cols * num_rows) % num_cols;
            std::cout << r << " " << c << " " << h << std::endl;
        }

        std::cout << len_path_ << std::endl;
    }

    void test()
    {
        // std::vector<std::string> map = {"########",
        //                                 "#.....@.",
        //                                 ".....###",
        //                                 "........",
        //                                 "#.#####*",
        //                                 ".$......",
        //                                 "........",
        //                                 "........"};
        std::vector<std::string> map = {"@........",
                                        ".##.###.#",
                                        "......#..",
                                        ".##$###.#",
                                        ".*......."};
        handler(map);
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
