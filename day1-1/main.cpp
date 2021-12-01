#include <iostream>
#include <fstream>
#include "string"

int main() {
    std::string line;
    std::ifstream if_input("input.txt");
    int last_depth = INT_MAX;
    int count = 0;

    while (std::getline(if_input, line)) {
        int cur_depth = std::stoi(line);

        if (cur_depth > last_depth) {
            count++;
        }

        last_depth = cur_depth;
    }

    std::cout << count;

    return 0;
}
