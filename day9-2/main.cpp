#include <iostream>
#include <fstream>
#include "string"
#include <vector>
#include <algorithm>

const int WIDTH = 100;
const int HEIGHT = 100;

int heights[HEIGHT][WIDTH];

int calc_basin(int i, int j) {
    if (heights[i][j] == -1 || heights[i][j] == 9) {
        return 0;
    }

    int cur_total = 1;
    heights[i][j] = -1;

    if (j < WIDTH - 1) { // right
        cur_total += calc_basin(i, j + 1);
    }

    if (i < HEIGHT - 1) { // up
        cur_total += calc_basin(i + 1, j);
    }

    if (j != 0) { // left
        cur_total += calc_basin(i, j - 1);
    }

    if (i != 0) { // down
        cur_total += calc_basin(i - 1, j);
    }

    return cur_total;
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    int i = 0;
    while (std::getline(fin, line)) {
        int j = 0;

        for (const char &height: line) {
            heights[i][j] = height - '0';

            j++;
        }

        i++;
    }

    std::vector<int> basins;
    for (i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (heights[i][j] != 9 && heights[i][j] != -1) {
                basins.push_back(calc_basin(i, j));
            }
        }
    }

    std::ranges::sort(basins, std::greater<int>());

    std::cout << basins.at(0) * basins.at(1) * basins.at(2);

    return 0;
}
