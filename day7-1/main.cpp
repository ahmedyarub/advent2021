#include <iostream>
#include <fstream>
#include "string"
#include <vector>
#include <sstream>
#include <array>
#include <algorithm>

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;
    std::getline(fin, line);

    std::vector<int> positions;

    std::stringstream ss(line);
    std::string substr;

    int max_pos = 0;
    while (getline(ss, substr, ',')) {
        int cur_pos = std::stoi(substr);
        if (cur_pos > max_pos) {
            max_pos = cur_pos;
        }

        positions.push_back(cur_pos);
    }

    std::ranges::sort(positions);
    int median = positions.at(positions.size() / 2);

     int total = 0;
    for (const auto &position: positions) {
        total += std::abs(position - median);
    }

    std::cout << total;

    return 0;
}
