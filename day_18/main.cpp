#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <numeric>

std::uint64_t evaluate(const std::string &expression, bool add_pref) {
    std::uint64_t result = 0;
    std::vector<std::uint64_t> nums;
    std::vector<char> ops;

    bool p = false;
    bool p_digit = false;
    int a_p = 0;

    std::string ev;
    std::string number;

    for (size_t i = 0; i < expression.length(); i++)
    {
        
        if(isdigit(expression[i]) && !p) {
            p_digit = true;
            number += expression[i];
        }
        if((!isdigit(expression[i]) || i+1 == expression.length()) && !p) {
            if(p_digit) {
                auto n = stoull(number);
                nums.push_back(n);
                number = "";
            }
            p_digit = false;
        }
        if((expression[i] == '+' || expression[i] == '*') && !p) {
            ops.push_back(expression[i]);
        }
        if(expression[i] == '(') {
            if(p && a_p > 0) {
                ev += '(';
            }
            p = true;
            a_p++;
            continue;
        }
        if(expression[i] == ')') {
            a_p--;
            if(a_p <= 0) {
                p = false;
                nums.push_back(evaluate(ev, add_pref));
                ev = "";
            }
        }
        if(p && a_p > 0) {
            ev += expression[i];
        }
    }

    std::uint64_t a = nums[0];
    int j = 0;
    int n = 0;
    if(add_pref) {
        std::string ex;
        for (size_t i = 0; i < nums.size() + ops.size(); i++)
        {

            if(i % 2 == 0) {
                ex += std::to_string(nums[n]);
                n++;
            } else {
                ex += ops[j];
                j++;
            }
        }

        std::stringstream st(ex);
        std::string curr;
        std::vector<uint64_t> factors;

        while(getline(st, curr, '*')) {
            factors.push_back(evaluate(curr, false));
        }
        
        result += std::accumulate(factors.begin(), factors.end(), static_cast<uint64_t>(1), std::multiplies<std::uint64_t>());
    } else {
        for (size_t i = 0; i < nums.size() - 1; i++)
        {
            std::uint64_t b = nums[i+1];

            if(ops[j] == '+') {
                a = a + b;
            }
            if(ops[j] == '*') {
                a = a * b;
            }
            j++;
        }
    }
    
    if(!add_pref) result = a;
    return result;
}

int main(int, char**) {
    std::ifstream file;
    std::string cur;
    file.open("input.txt");

    std::uint64_t p1 = 0;
    std::uint64_t p2 = 0;

    while(getline(file, cur)) {
        p1 += evaluate(cur, false);
        p2 += evaluate(cur, true);
    }

    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;

    file.close();
    return EXIT_SUCCESS;
}