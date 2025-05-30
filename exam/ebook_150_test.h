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

    // BFS
    void find_path(const std::vector<std::string> &map, int fr, int fc, int tr, int tc,
                  std::vector<std::vector<int>> &min_path, int &len_path)
    {
        const char wall = '#';
        int num_rows = map.size();
        int num_cols = map.empty() ? 0 : map[0].size();
        int total_points = num_rows * num_cols;

        min_path.clear();
        len_path = INF;
        if (fr < 0 || fr >= num_rows || fc < 0 || fc >= num_cols)
        {
            return;
        }

        if (tr < 0 || tr >= num_rows || tc < 0 || tc >= num_cols)
        {
            return;
        }

        if (map[fr][fc] == wall || map[tr][tc] == wall)
        {
            return;
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

        static std::vector<std::vector<std::vector<int>>> trace;
        trace.resize(num_rows);
        for (auto &i : trace)
        {
            i.resize(num_cols);
            for (auto &j : i)
            {
                j.resize(2);
                j[0] = UNASSIGN;
                j[1] = UNASSIGN;
            }
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
                        trace[nr][nc][0] = r;
                        trace[nr][nc][1] = c;
                    }
                }
            }

            if(cost[tr][tc] != INF){
                break;
            }
        }

        len_path = cost[tr][tc];
        if (len_path != INF)
        {
            min_path.reserve(len_path + 1);
            int r = tr, c = tc;
            while(true)
            {
                min_path.push_back({r, c});
                if (r == fr && c == fc)
                {
                    break;
                }
                r = trace[r][c][0];
                c = trace[r][c][1];
            }
            std::reverse(min_path.begin(), min_path.end());
        }
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

        std::vector<std::vector<int>> lst_pos;
        lst_pos.reserve(min_path_.size());
        for (auto val : min_path_)
        {
            int h = val / (num_cols * num_rows);
            int r = (val - h * num_cols * num_rows) / num_cols;
            int c = (val - h * num_cols * num_rows) % num_cols;
            lst_pos.push_back({r, c, r + delta[h][0], c + delta[h][1]});
        }
        
        std::string path;
        path.reserve(len_path_);

        tmp = map[start_r][start_c];
        map[start_r][start_c] = wall;
        std::vector<std::vector<int>> path0;
        int len0;
        find_path(map, star_r, star_c, lst_pos[0][2], lst_pos[0][3], path0, len0);
        for (int i = 1; i < path0.size(); i++)
        {
            int dtr = path0[i][0] - path0[i - 1][0];
            int dtc = path0[i][1] - path0[i - 1][1];
            if (dtr == 1)
            {
                path.push_back('s');
            }
            else if (dtr == -1)
            {
                path.push_back('n');
            }
            if (dtc == 1)
            {
                path.push_back('e');
            }
            else if (dtc == -1)
            {
                path.push_back('w');
            }
        }
        map[start_r][start_c] = tmp;

        for (int i = 0; i < lst_pos.size() - 1; i++)
        {
            int r = lst_pos[i][2];
            int c = lst_pos[i][3];
            int rr = lst_pos[i][0];
            int cc = lst_pos[i][1];
            int nr = lst_pos[i + 1][2];
            int nc = lst_pos[i + 1][3];

            tmp = map[rr][cc];
            map[rr][cc] = wall;
            std::vector<std::vector<int>> path1;
            int len1;
            find_path(map, r, c, nr, nc, path1, len1);
            for (int i = 1; i < path1.size() - 1; i++)
            {
                int dtr = path1[i][0] - path1[i - 1][0];
                int dtc = path1[i][1] - path1[i - 1][1];
                if (dtr == 1)
                {
                    path.push_back('s');
                }
                else if (dtr == -1)
                {
                    path.push_back('n');
                }
                if (dtc == 1)
                {
                    path.push_back('e');
                }
                else if (dtc == -1)
                {
                    path.push_back('w');
                }
            }
            {
                int j = path1.size() - 1;
                int dtr = path1[j][0] - path1[j - 1][0];
                int dtc = path1[j][1] - path1[j - 1][1];
                if (dtr == 1)
                {
                    path.push_back('S');
                }
                else if (dtr == -1)
                {
                    path.push_back('N');
                }
                if (dtc == 1)
                {
                    path.push_back('E');
                }
                else if (dtc == -1)
                {
                    path.push_back('W');
                }
            }
            map[rr][cc] = tmp;
        }

        std::cout << len_path_ << std::endl;
        std::cout << path << std::endl;
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

namespace test4_150 {
    void hander(const std::vector<int> &input, int k, std::vector<int> &result){
        int n = input.size();
        std::vector<std::vector<int>> mat;

        mat.resize(k);
        for(int i = 0; i < k; i++){
            mat[i].resize(n);
        }

        for(int r = 0; r < k ; r++){
            mat[r][0] = -1;
        }
        mat[input[0] % k][0] = 1;
        for(int i =0; i < n; i++){
            mat[0][i] = 0;
        }

        for (int c = 1; c < n; c++)
        {
            for (int r = 1; r < k; r++)
            {
                int val = r - input[c] % k;
                if (val < 0)
                {
                    val += k;
                }
                if (mat[val][c - 1] >= 0 && mat[r][c - 1] >= 0)
                {
                    mat[r][c] = std::min(mat[r][c - 1], mat[val][c - 1] + 1);
                }
                else if (mat[val][c - 1] >= 0)
                {
                    mat[r][c] = mat[val][c - 1] + 1;
                }
                else if (mat[r][c - 1] >= 0)
                {
                    mat[r][c] = mat[r][c - 1];
                }
                else
                {
                    mat[r][c] = -1;
                }
            }
        }

        result.reserve(n);

        int mod = 0;
        for(auto &i: input){
            mod += i % k;
        }
        mod = mod % k;
        auto val = mat[mod][n - 1];
        if (val == -1)
        {
            return;
        }

        for(int c = n -1; c >= 1; c--){
            if(mat[mod][c] == mat[mod][c - 1]){
                result.push_back(c);
            }
            else{
                mod = mod - input[c];
                if(mod < 0){
                    mod = k + mod;
                }
            }
        }
        if(mat[mod][0] <= 0){
            result.push_back(0);
        }
    }
    
    void test(){
        std::vector<int> intput = {2, 7, 3, 5,  9, 6, 12, 7, 11, 15}, result;
        int k = 3;
        hander(intput, k, result);
        for(auto i: result){
            std:: cout << i << " ";
        }
    }
}

namespace test5_150{
    const int N = 35;
    const int M = 25;

    std::vector<std::string> fn;

    void findCost(const std::string &s, int n, std::vector<int> &cost){
        fn.resize(n);
        fn[0] = "A";
        fn[1] = "B";

        cost.resize(n);
        cost[0] = cost[1] = 0;
        for (int i = 2; i < n; i++)
        {
            fn[i] = fn[i - 2] + fn[i - 1];
            auto &lst = fn;
            auto &val = fn[i];
            int count = 0;

            int from = fn[i - 2].size() - s.size() + 1;
            int to = fn[i - 2].size() - 1;

            from = std::max(from, 0);
            to = std::min(to, (int)(fn[i].size() - s.size()));

            for (int j = from; j <= to; j++)
            {
                bool check = true;
                for (int t = 0; t < s.size(); t++)
                {
                    if (s[t] != val[j + t])
                    {
                        check = false;
                        break;
                    }
                }
                if (check)
                {
                    count++;
                }
            }

            cost[i] = count;
        }
    }

    void handler(const std::string &s, int n)
    {
        std::vector<int> cost;
        findCost(s, n, cost);

        std::vector<int> results(n);
        if (s == fn[0])
        {
            results[0] = 1;
        }
        if (s == fn[1])
        {
            results[1] = 1;
        }
        for (int i = 2; i < n; i++)
        {
            results[i] = results[i - 2] + results[i - 1] + cost[i];
        }

        std::cout << results[n] << std::endl;
    }

    void test(){
        std::string s = "BABBAB";
        handler(s, 8);
    }
}


namespace test6_150{
    bool is_prime(int n)
    {
        if (n == 2)
        {
            return true;
        }
        else if (n < 2)
        {
            return false;
        }
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    void find(const std::vector<bool> &primes, int id, int m, std::vector<int> &arr, std::vector<bool> &visited,
              std::vector<std::vector<int>> &results)
    {
        if (id == arr.size())
        {
            if (primes[arr[id - 1] + arr[0]])
            {
                results.push_back(arr);
            }
            return;
        }

        for (int i = 2; i <= m; i++)
        {
            if (primes[i + arr[id - 1]] && !visited[i])
            {
                visited[i] = true;
                arr[id] = i;
                find(primes, id + 1, m, arr, visited, results);

                visited[i] = false;
            }
        }
    }

    void handler(int n){
        int m = n * 2;
        std::vector<bool> primes(2 * m + 1);
        for (int i = 2; i < primes.size(); i++)
        {
            primes[i] = is_prime(i);
        }

        std::vector<int> arr(m);
        arr[0] = 1;

        std::vector<bool> check(m + 1, false);
        check[arr[0]] = true;

        std::vector<std::vector<int>> results;
        find(primes, 1, m, arr, check, results);

        std::cout << results.size() << std::endl;
        for (auto &result : results)
        {
            for (auto &val : result)
            {
                std::cout << val << ' ';
            }
            std::cout << std::endl;
        }
    }

    void test(){
        handler(4);
    }
}

namespace test7_150
{
    const int UNASSIGN = -1, INF = 1e9;

    void find_path(const std::vector<std::vector<int>> &traces, int point, std::vector<int> &path,
                   std::vector<std::vector<int>> &paths)
    {
        if(traces[point].empty()){
            paths.push_back(path);
            return;
        }

        for(auto &p:traces[point]){
            path.push_back(p);
            find_path(traces, p, path, paths);
            path.pop_back();
        }
    }

    void find_path(const std::vector<std::vector<int>> &cost, int start, int stop,
                   std::vector<std::vector<int>> &paths, int &len_path)
    {
        int num_points = cost.size();
        std::vector<bool> free(num_points, true);
        std::vector<int> dist(num_points, INF);
        std::vector<std::vector<int>> trace(num_points);

        dist[start] = 0;
        while (true)
        {
            int min_point = UNASSIGN, min_dist = INF;
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
                if (free[point])
                {
                    int val = dist[min_point] + cost[min_point][point];
                    if (val < dist[point])
                    {
                        dist[point] = val;
                        trace[point] = {min_point};
                    }
                    else if(val == dist[point]){
                        trace[point].push_back(min_point);
                    }
                }
            }
        }

        if(!free[stop]){
            len_path = dist[stop];
            std::vector<int> path = {stop};
            find_path(trace, stop, path, paths);
        }
        else{
            len_path = INF;
            paths.clear();
        }
    }

    void handler(const std::vector<std::vector<int>> &cost, int ha, int sa, int hb, int sb)
    {
        std::vector<std::vector<int>> a_paths, b_paths;
        int len_a, len_b;
        find_path(cost, ha, sa, a_paths, len_a);
        find_path(cost, hb, sb, b_paths, len_b);
        
        int num_points = cost.size();
        std::vector<int> cost_a(num_points, INF);
        std::vector<int> cost_b(num_points, INF);

        for(auto &path: a_paths){
            std::reverse(path.begin(), path.end());
            int sum = 0;
            for(int i = 1; i < path.size(); i++){
                cost_a[path[i]] = sum + cost[path[i]][path[i - 1]];
                sum +=  cost[path[i]][path[i - 1]];
            }
        }
        
        for(auto &path: b_paths){
            std::reverse(path.begin(), path.end());
            int sum = 0;
            for(int i = 1; i < path.size(); i++){
                cost_b[path[i]] = sum + cost[path[i]][path[i - 1]];
                sum +=  cost[path[i]][path[i - 1]];
            }
        }

        int min_time = INF, min_point = UNASSIGN;
        for(int i = 0; i < num_points; i++){
            auto val = std::max(cost_a[i], cost_b[i]);
            if(min_time > val){
                min_point = i;
                min_time = val;
            }
        }

        int id_a = UNASSIGN, id_b = UNASSIGN;
        for(int i = 0; i < a_paths.size() && id_a == UNASSIGN; i++){
            for(int j = 0; j < a_paths[i].size(); j++){
                if(min_point == a_paths[i][j]){
                    id_a = i;
                    break;
                }
            }
        }

        for(int i = 0; i < b_paths.size() && id_b == UNASSIGN; i++){
            for(int j = 0; j < b_paths[i].size(); j++){
                if(min_point == b_paths[i][j]){
                    id_b = i;
                    break;
                }
            }
        }

        std::cout << len_a << std::endl;
        for(auto point: a_paths[id_a]){
            std::cout << (point + 1) <<  " ";
        }
        std::cout << std::endl;

        std::cout << len_b << std::endl;
        for(auto point: b_paths[id_b]){
            std::cout << (point + 1) <<  " ";
        }
        std::cout << std::endl;

        std::cout << (min_point + 1) << std::endl << min_time;
    }

    void test()
    {
        std::vector<std::vector<int>> cost = {
            {INF, INF, 10 , 10 , INF, INF}, 
            {INF, INF, 5  , INF, INF, INF},
            {10 , 5  , INF, 5  , INF, 15 }, 
            {10 , INF, 5  , INF, 20 , 15 }, 
            {INF, INF, INF, 20 , INF, INF},
            {INF, INF, 15 , 15 , INF, INF}};
        int ha = 1, sa = 6, hb = 2, sb = 5;
        handler(cost, ha - 1, sa - 1, hb - 1, sb - 1);
    }
}

namespace test8_150
{
    const int W = 1000;

    void compare(const std::string &content, const std::string &p, std::vector<int> &first, std::vector<int> &last){
        first.resize(content.size());
        last.resize(content.size());
        for(int from = 0; from < content.size(); from++){
            int count = 0;
            for(int to = 0; to < p.size() && from + to < content.size(); to++){
                if (content[from + to] == p[to])
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            first[from] = count;
        }

        for (int from = 0; from < content.size(); from++)
        {
            int count = 0;
            for (int to = p.size() - 1; to >= 0 && from - to >= 0; to--)
            {
                if (content[from - to] == p[to])
                {
                    count++;
                }
                {
                    break;
                }
            }
            last[from] = count;
        }
    }

    void handler(const std::string &content, const std::string &p){
        std::vector<int> first, last;
        compare(content, p, first, last);

        int id = 0, count = 0;
        for(int i = 0; i < content.size(); i++){
            for (int j = 0; j < content.size(); j++)
            {
                if (i <= j && first[i] + last[j] >= p.size())
                {
                    if ((j - i + 1) > p.size())
                    {
                        count++;
                        id++;

                        break;
                    }
                    else if ((j - i + 1) == p.size())
                    {
                        count += (i - id + 1);
                        id = i + 1;

                        break;
                    }
                }
            }
        }

        std::cout << count << std::endl;
    }

    void test(){
        const std::string content = "This is a sample text for the first task on the contest", p = "is";
        handler(content, p);
    }
}

namespace test9_150
{
    void find_max(const std::vector<int> &s1, const std::vector<int> &s2, std::vector<int> &s)
    {
        std::vector<std::vector<int>> cost(s1.size() + 1);
        for (int i = 0; i <= s1.size(); i++)
        {
            cost[i].resize(s2.size() + 1);
        }

        for (int i = 0; i <= s1.size(); i++)
        {
            cost[i][0] = 0;
        }

        for (int i = 0; i <= s2.size(); i++)
        {
            cost[0][i] = 0;
        }

        for (int n1 = 1; n1 <= s1.size(); n1++)
        {
            for (int n2 = 1; n2 <= s2.size(); n2++)
            {
                if (s1[n1 - 1] == s2[n2 - 1])
                {
                    cost[n1][n2] = 1 + cost[n1 - 1][n2 - 1];
                }
                else
                {
                    cost[n1][n2] = std::max(cost[n1 - 1][n2], cost[n1][n2 - 1]);
                }
            }
        }

        int n1 = s1.size(), n2 = s2.size();
        s.resize(cost[s1.size()][s2.size()]);

        int count = s.size() - 1;
        while (n1 != 0 && n2 != 0)
        {
            if (s1[n1 - 1] == s2[n2 - 1])
            {
                s[count--] = s1[n1 - 1];
                n1--;
                n2--;
            }
            else if (cost[n1][n2] == cost[n1][n2 - 1])
            {
                n2--;
            }
            else
            {
                n1--;
            }
        }
        std::cout << "";
    }

    void handler(const std::vector<int> &s1, const std::vector<int> &s2)
    {
        std::vector<int> s, ss;
        auto ss1 = s1, ss2 = s2;
        for (int i = 0; i < s2.size() - 1; i++)
        {
            auto val = ss2[ss2.size() - 1];
            for (int j = ss2.size() - 1; j > 0; j--)
            {
                ss2[j] = ss2[j - 1];
            }
            ss2[0] = val;
            find_max(ss1, ss2, ss);
            if(ss.size() > s.size()){
                s = ss;
            }
        }
        std::cout << s.size() << std::endl;
        for (auto val : s)
        {
            std::cout << val << std::endl;
        }
    }

    void test()
    {
        std::vector<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8}, s2 = {2, 4, 6, 8, 1, 2, 3}, s;
        handler(s1, s2);
    }
}

namespace test10_150
{
    const int UNASSIGN = -1;
    void find_max(const std::vector<int> &start, const std::vector<int> &stop, std::vector<int> &result)
    {
        std::vector<std::vector<bool>> parents(start.size());
        for (int i = 0; i < start.size(); i++)
        {
            parents[i].resize(start.size());
        }
        for (int i = 0; i < start.size(); i++)
        {
            int si = start[i], fi = stop[i];
            for (int j = 0; j < start.size(); j++)
            {
                int sj = start[j], fj = stop[j];
                parents[i][j] = fj <= si;
            }
        }

        std::vector<int> cost(start.size(), 1), trace(start.size(), UNASSIGN);
        while (true)
        {
            int count = 0;
            for (int i = 0; i < start.size(); i++)
            {
                for (int j = 0; j < start.size(); j++)
                {
                    if (parents[i][j])
                    {
                        if (cost[i] < cost[j] + 1)
                        {
                            cost[i] = cost[j] + 1;
                            trace[i] = j;
                            count++;
                        }
                    }
                }
            }

            if (count == 0)
            {
                break;
            }
        }

        int id_max = 0;
        for(int i = 0 ; i < start.size(); i++){
            if(cost[i] > cost[id_max]){
                id_max = i;
            }
        }

        int id = id_max;
        while(id != UNASSIGN){
            result.push_back(id);
            id = trace[id];
        }
        std::reverse(result.begin(), result.end());
    }

    void handler(const std::vector<int> &start, const std::vector<int> &stop)
    {
        std::vector<int> result;
        find_max(start, stop, result);
        std::cout << result.size() << std::endl;
        for (auto &val : result)
        {
            std::cout << val + 1 << std::endl;
        }
    }

    void test()
    {
        std::vector<int> start = {7, 2, 1, 1, 3};
        std::vector<int> stop = {9, 4, 3, 6, 7};
        handler(start, stop);
    }
}

namespace test11_150 {
    const int INF = 1e9, UNASSIGN = -1;

    void find_min(const std::vector<std::vector<int>> &cost, int s, int f, int &min_path, std::vector<int> &path)
    {
        int num_points = cost.size();
        std::vector<int> dist(num_points, INF);
        std::vector<int> trace(num_points, UNASSIGN);
        std::vector<bool> free(num_points, true);

        dist[s] = 0;
        while (true)
        {
            int min_point = UNASSIGN, min_dist = INF;
            for (int point = 0; point < num_points; point++)
            {
                if (free[point])
                {
                    if (dist[point] < min_dist)
                    {
                        min_point = point;
                        min_dist = dist[point];
                    }
                }
            }

            if (min_point == UNASSIGN)
            {
                break;
            }

            free[min_point] = false;
            if (min_point == f)
            {
                break;
            }

            for (int point = 0; point < num_points; point++)
            {
                if (free[point] && cost[min_point][point] != INF)
                {
                    if (dist[min_point] + cost[min_point][point] < dist[point])
                    {
                        dist[point] = dist[min_point] + cost[min_point][point];
                        trace[point] = min_point;
                    }
                }
            }
        }

        min_path = dist[f];
        int id = f;
        while (id != UNASSIGN)
        {
            path.push_back(id);
            id = trace[id];
        }
        std::reverse(path.begin(), path.end());
    }

    void handler(int l1, int l2, int l3, int c1, int c2, int c3, int s, int f, const std::vector<int> &dist)
    {
        std::vector<int> pos = {0};
        pos.insert(pos.end(), dist.begin(), dist.end());

        int num_points = pos.size();
        std::vector<std::vector<int>> cost(num_points);
        for (auto &val : cost)
        {
            val.resize(num_points);
        }

        for (int i = 0; i < num_points; i++)
        {
            for (int j = i + 1; j < num_points; j++)
            {
                int d = pos[j] - pos[i];
                if (d <= l1)
                {
                    cost[i][j] = cost[j][i] = c1;
                }
                else if (d <= l2)
                {
                    cost[i][j] = cost[j][i] = c2;
                }
                else if (d <= l3)
                {
                    cost[i][j] = cost[j][i] = c3;
                }
                else
                {
                    cost[i][j] = cost[j][i] = INF;
                }
            }
        }

        int min_path;
        std::vector<int> path;
        find_min(cost, s - 1, f -1, min_path, path);

        std::cout << min_path << std::endl;
    }

    void test()
    {
        int l1 = 3, l2 = 6, l3 = 8, c1 = 20, c2 = 30, c3 = 40;
        int s = 2, f = 6;
        std::vector<int> dist = {3, 7, 8, 13, 15, 23};
        handler(l1, l2, l3, c1, c2, c3, s, f, dist);
    }
}