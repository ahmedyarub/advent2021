#include <iostream>
#include <fstream>
#include "string"

int main() {
    std::fstream fin("input.txt", std::fstream::in);

    int horizontal = 0;
    int vertical = 0;
    char ch = ' ';

    while (!fin.eof()) {
        do {
            fin >> ch;
        } while (ch == 10 || ch == 13);

        char direction = ch;

        while (ch != ' ') {
            fin >> std::noskipws >> ch;
        }

        fin >> ch;
        int val = ch - '0';

        switch (direction) {
            case 'f':
                horizontal += val;
                break;
            case 'd':
                vertical += val;
                break;
            case 'u':
                vertical -= val;
                break;
            default:
                return -1;
        }

        fin >> ch;
    }

    std::cout << vertical * horizontal;

    return 0;
}
