#include <iostream>
#include <fstream>
#include "string"
#include <vector>
#include <sstream>
#include <map>
#include <array>
#include <numeric>

const int DAYS = 80;

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;
    std::getline(fin, line);

    std::vector<int> counters;

    std::stringstream ss(line);
    std::string substr;

    while (getline(ss, substr, ',')) {
        counters.push_back(std::stoi(substr));
    }

    for (int i = 0; i < DAYS; i++) {
        int to_create = 0;
        int min_counter = INT_MAX;

        for (auto &counter: counters) {
            if (counter < min_counter) {
                min_counter = counter;
            }

            if (counter == 0) {
                to_create++;
                counter = 6;
            } else {
                counter--;
            }
        }

        if (to_create) {
            for (int j = 0; j < to_create; j++) {
                counters.emplace_back(8);
            }
        } else {
            for (auto &counter: counters) {
                counter -= (min_counter - 1); // we already subracted 1 from all counters
            }

            i += (min_counter - 1);
        }
    }

    std::cout << counters.size();

    return 0;
}
