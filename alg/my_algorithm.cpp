#include "my_algorithm.h"

namespace alg
{

    int64_t find_gcd(int64_t a, int64_t b)
    {
        if (a < b)
        {
            int64_t c = a;
            a = b;
            b = c;
        }

        while (b != 0)
        {
            int64_t r = a % b;
            a = b;
            b = r;
        }

        return a;
    }

    void find_euclid_extended(int64_t a, int64_t b, int64_t &x, int64_t &y, int64_t &c)
    {
        int64_t x0 = 1, y0 = 0, x1 = 0, y1 = 1;
        while (b > 0)
        {
            int64_t r = a % b;
            if (r == 0)
                break;
            int64_t q = a / b;
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

    std::vector<int64_t> find_linear_congruence(int64_t a, int64_t b, int64_t n)
    {
        a = a % n;
        int64_t v, u, d;
        find_euclid_extended(n, a, v, u, d);
        if (b % d != 0)
        {
            return {};
        }
        int64_t x0 = (u * (b / d)) % n;
        std::vector<int64_t> r;
        for (int i = 0; i < d; i++)
        {
            r.push_back((x0 + i * n / d) % n);
        }
        return r;
    }

    int64_t cal_ckn(int64_t k, int64_t n)
    {
        int64_t t = 1, m = 1;
        for (int64_t i = k + 1; i <= n; i++)
        {
            t *= i;
        }
        for (int64_t i = 2; i <= n - k; i++)
        {
            m *= i;
        }
        return t / m;
    }

    int64_t cal_large_ckn(int64_t k, int64_t n)
    {
        int64_t t = 1, m = 1, g;
        for (int64_t i = k + 1; i <= n; i++)
        {
            t *= i;
            m *= (i - k);
            g = find_gcd(t, m);
            t /= g;
            m /= g;
        }
        return t / m;
    }

    int64_t cal_akn(int64_t k, int64_t n)
    {
        int64_t a = 1;
        for (int64_t i = n - k + 1; i <= n; i++)
        {
            a *= i;
        }
        return a;
    }

    double calPostfix(const std::string &str)
    {
        list<string> listContents;
        istringstream iss(str);
        string word;
        while (iss >> word)
        {
            listContents.push_back(word);
        }

        list<double> stack;
        for (auto &i : listContents)
        {
            bool checkNumber = true;
            for (auto &c : i)
            {
                if (c < '0' || c > '9')
                {
                    checkNumber = false;
                    break;
                }
            }

            if (checkNumber)
            {
                double val = stod(i);
                stack.push_back(val);
            }
            else
            {
                double second = stack.back();
                stack.pop_back();

                double first = stack.back();
                stack.pop_back();

                double exe = 0;
                if (i == "+")
                {
                    exe = first + second;
                }
                else if (i == "-")
                {
                    exe = first - second;
                }
                else if (i == "*")
                {
                    exe = first * second;
                }
                else if (i == "/")
                {
                    exe = first / second;
                }

                stack.push_back(exe);
            }
        }

        return stack.back();
    }

    string infix2Postfix(const string &str){
        map<string, int> cost;
        cost["("] = 0;
        cost[")"] = 0;
        cost["+"] = 1;
        cost["-"] = 1;
        cost["*"] = 2;
        cost["/"] = 2;

        list<string> listContents;
        istringstream iss(str);
        string word;
        while (iss >> word)
        {
            listContents.push_back(word);
        }

        string result;
        result.reserve(str.size());

        list<string> stack;
        for(auto &s:listContents){
            bool checkNumber = true;
            for(auto &i:s){
                if(i < '0' || i > '9'){
                    checkNumber = false;
                    break;
                }
            }

            if(checkNumber){
                result += s + " ";
            }
            else{
                if(s == "("){
                    stack.push_back(s);
                }
                else if(s == ")"){
                    while(stack.back() != "("){
                        result += stack.back() + " ";
                        stack.pop_back();
                    }
                    stack.pop_back();
                }
                else if(s == "+" || s == "-" || s== "*" || s == "/"){
                    if(!stack.empty()){
                    while(cost[s] <= cost[stack.back()]){
                        result += stack.back() + " ";
                        stack.pop_back();
                    }
                    }
                    stack.push_back(s);
                }
            }

        }

        while(stack.size()){
            result += stack.back() + " ";
            stack.pop_back();
        }
        return result;
    }
}