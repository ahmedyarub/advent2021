#include <iostream>
#include <fstream>
#include <map>
#include <queue>

const int WIDTH = 500;
const int HEIGHT = 500;

int map[WIDTH][HEIGHT];
int shortest_path[WIDTH][HEIGHT] = {0};

void calc_risk(int start_i, int start_j) {
    std::deque<std::pair<int, int>> point_queue;

    point_queue.emplace_back(start_i, start_j);
    shortest_path[start_i][start_j] = 0;

    while (!point_queue.empty()) {
        auto cur_point = point_queue.front();
        point_queue.pop_front();

        auto[i, j] = cur_point;

        if (i + 1 <= (WIDTH - 1) &&
            (shortest_path[i + 1][j] == 0 || shortest_path[i][j] + map[i + 1][j] < shortest_path[i + 1][j])) {
            shortest_path[i + 1][j] = shortest_path[i][j] + map[i + 1][j];
            point_queue.emplace_back(i + 1, j);
        }

        if (j + 1 <= (HEIGHT - 1) &&
            (shortest_path[i][j + 1] == 0 || shortest_path[i][j] + map[i][j + 1] < shortest_path[i][j + 1])) {
            shortest_path[i][j + 1] = shortest_path[i][j] + map[i][j + 1];
            point_queue.emplace_back(i, j + 1);
        }

        if (i - 1 >= 0 &&
            (shortest_path[i - 1][j] == 0 || shortest_path[i][j] + map[i - 1][j] < shortest_path[i - 1][j])) {
            shortest_path[i - 1][j] = shortest_path[i][j] + map[i - 1][j];
            point_queue.emplace_back(i - 1, j);
        }

        if (j - 1 >= 0 &&
            (shortest_path[i][j - 1] == 0 || shortest_path[i][j] + map[i][j - 1] < shortest_path[i][j - 1])) {
            shortest_path[i][j - 1] = shortest_path[i][j] + map[i][j - 1];
            point_queue.emplace_back(i, j - 1);
        }
    }
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    int j = 0;
    while (std::getline(fin, line)) {
        int i = 0;

        for (auto risk: line) {
            int risk_val = risk - '0';

            for (int m = 0; m < 5; m++) {
                for (int n = 0; n < 5; n++) {
                    int cur_risk = risk_val + m + n;

                    if (cur_risk > 9) {
                        cur_risk -= 9;
                    }

                    map[m * 100 + i][n * 100 + j] = cur_risk;
                }
            }

            i++;
        }

        j++;
    }

    calc_risk(0, 0);

    std::cout << shortest_path[WIDTH - 1][HEIGHT - 1];

    return 0;
}
