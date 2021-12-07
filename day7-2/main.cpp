#include <iostream>
#include <fstream>
#include "string"
#include <vector>
#include <sstream>
#include <array>
#include <map>

std::map<int, int> sums;

int sum_upto(int n) {
    if (sums.contains(n)) {
        return sums.at(n);
    }

    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += i;
    }

    sums.insert(std::pair<int, int>(n, total));

    return total;
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;
    std::getline(fin, line);

    std::vector<int> positions;

    std::stringstream ss(line);
    std::string substr;

    int max_pos = 0;
    int pos_total = 0;
    while (getline(ss, substr, ',')) {
        int cur_pos = std::stoi(substr);
        if (cur_pos > max_pos) {
            max_pos = cur_pos;
        }
        pos_total += cur_pos;
        positions.push_back(cur_pos);
    }

    int average = pos_total / positions.size();
    int total = 0;

    for (const auto &position: positions) {
        total += sum_upto(std::abs(position - average));
    }


    std::cout << total;

    return 0;
}
