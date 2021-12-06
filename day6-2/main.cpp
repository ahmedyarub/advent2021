#include <iostream>
#include <fstream>
#include "string"
#include <vector>
#include <sstream>
#include <map>
#include <array>
#include <numeric>

const int DAYS = 256;

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;
    std::getline(fin, line);

    std::stringstream ss(line);
    std::string substr;

    std::array<long long int, DAYS> born_at_day = {0};
    long long int count = 0;

    while (getline(ss, substr, ',')) {
        count++;
        int cur_day = std::stoi(substr);

        while (cur_day < DAYS) {
            born_at_day.at(cur_day)++;

            cur_day += 7;
        }
    }

    for (int i = 0; i < DAYS; i++) {
        auto born_today = born_at_day.at(i);
        if (born_today > 0) {
            count += born_today;
            int cur_day = i + 9;

            while (cur_day < DAYS) {
                born_at_day.at(cur_day) += born_today;
                cur_day += 7;
            }
        }
    }

    std::cout << count;

    return 0;
}
