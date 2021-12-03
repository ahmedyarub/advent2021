#include <iostream>
#include <fstream>
#include "string"

const int WORD_SIZE = 12;
int counts[WORD_SIZE] = {};

int main() {
    std::fstream fin("input.txt", std::fstream::in);

    int gamma = 0;
    int epsilon = 0;
    char ch;
    int cur_digit = 0;
    int lines = 0;

    while (!fin.eof()) {
        lines++;

        while (cur_digit < WORD_SIZE) {
            fin >> ch;
            counts[cur_digit++] += (ch == '1' ? 1 : 0);
        }

        cur_digit = 0;
    }

    for (auto count: counts) {
        gamma = gamma * 2 + (count > lines / 2 ? 1 : 0);
        epsilon = epsilon * 2 + (count < lines / 2 ? 1 : 0);
    }

    std::cout << gamma * epsilon;

    return 0;
}
