#include <iostream>
#include <fstream>
#include "string"
#include <stack>
#include <vector>
#include <algorithm>

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    std::vector<long long int> scores;
    while (std::getline(fin, line)) {
        std::stack<char> chars;

        bool corrupted = false;
        for (const char &chr: line) {
            if (chr == '(' || chr == '[' || chr == '{' || chr == '<') {
                chars.push(chr);
            } else if (chars.top() == '(' && chr == ')' ||
                       chars.top() == '[' && chr == ']' ||
                       chars.top() == '{' && chr == '}' ||
                       chars.top() == '<' && chr == '>') {
                chars.pop();
            } else {
                corrupted = true;
                break;
            }
        }

        if (corrupted) {
            continue;
        }

        long long int total = 0;
        while (!chars.empty()) {
            total *= 5;

            switch (chars.top()) {
                case '(':
                    total += 1;
                    break;
                case '[':
                    total += 2;
                    break;
                case '{':
                    total += 3;
                    break;
                case '<':
                    total += 4;
                    break;
                default:
                    return -1;
            }

            chars.pop();
        }


        scores.push_back(total);
    }

    std::ranges::nth_element(scores, scores.begin() + scores.size() / 2);

    std::cout << scores.at(scores.size() / 2);

    return 0;
}
