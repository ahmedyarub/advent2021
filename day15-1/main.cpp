#include <iostream>
#include <fstream>
#include "string"
#include <map>

const int WIDTH = 100;
const int HEIGHT = 100;

int map[WIDTH][HEIGHT];
int shortest_path[WIDTH][HEIGHT] = {0};

void calc_risk(int i, int j, int prev_total) {
    if (i < 0 || j < 0 || i == WIDTH || j == HEIGHT) {
        return;
    }

    int cur_total = prev_total + map[i][j];

    if (shortest_path[i][j] == 0 || cur_total < shortest_path[i][j]) {
        shortest_path[i][j] = cur_total;

        calc_risk(i + 1, j, cur_total);
        calc_risk(i, j + 1, cur_total);
        calc_risk(i - 1, j, cur_total);
        calc_risk(i, j - 1, cur_total);
    }
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    int j = 0;
    while (std::getline(fin, line)) {
        int i = 0;

        for (auto risk: line) {
            map[i][j] = risk - '0';

            i++;
        }

        j++;
    }

    calc_risk(WIDTH - 1, HEIGHT - 1, 0);

    std::cout << shortest_path[0][0] - map[0][0];

    return 0;
}
