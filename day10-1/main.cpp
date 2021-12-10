#include <iostream>
#include <fstream>
#include "string"
#include <stack>

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    int total = 0;
    while (std::getline(fin, line)) {
        std::stack<char> chars;

        for (const char &chr: line) {
            if (chr == '(' || chr == '[' || chr == '{' || chr == '<') {
                chars.push(chr);
            } else if (chars.top() == '(' && chr == ')' ||
                       chars.top() == '[' && chr == ']' ||
                       chars.top() == '{' && chr == '}' ||
                       chars.top() == '<' && chr == '>') {
                chars.pop();
            } else {
                switch (chr) {
                    case ')':
                        total += 3;
                        break;
                    case ']':
                        total += 57;
                        break;
                    case '}':
                        total += 1197;
                        break;
                    case '>':
                        total += 25137;
                        break;
                    default:
                        return -1;
                }

                break;
            }
        }

    }

    std::cout << total;

    return 0;
}
