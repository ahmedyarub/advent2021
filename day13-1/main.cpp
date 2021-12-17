#include <iostream>
#include <fstream>
#include <string>

const int MAX_WIDTH = 2000;
const int MAX_HEIGHT = 4000;
int dots[MAX_WIDTH][MAX_HEIGHT] = {0};

int count = 0;

void fold_x(int x) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            if (dots[i][j] == 1 || dots[x * 2 - i][j]) {
                dots[i][j] = 1;
                count++;
            } else {
                dots[i][j] = 0;
            }

            dots[x * 2 - i][j] = 0;
        }
    }
}

void fold_y(int y) {
    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < y; j++) {
            if (dots[i][j] == 1 || dots[i][y * 2 - j]) {
                dots[i][j] = 1;
                count++;
            } else {
                dots[i][j] = 0;
            }

            dots[i][y * 2 - j] = 0;
        }
    }
}

int count_ones() {
    int total = 0;

    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            total += dots[i][j];
        }
    }

    return total;
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    while (std::getline(fin, line)) {
        if (!line.empty()) {
            if (line.at(0) != 'f') {
                auto delimiter_pos = line.find(',');

                int x = stoi(line.substr(0, delimiter_pos));
                int y = stoi(line.substr(delimiter_pos + 1, line.size()));

                dots[x][y] = 1;
            } else {
                if (line.at(11) == 'y') {
                    fold_y(stoi(line.substr(13, -1)));
                    break;
                } else {
                    fold_x(stoi(line.substr(13, -1)));
                    break;
                }
            }
        }
    }


    std::cout << count;

    return 0;
}
