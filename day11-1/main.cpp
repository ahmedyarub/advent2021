#include <iostream>
#include <fstream>
#include "string"

const int WIDTH = 10;
const int HEIGHT = 10;
const int STEPS = 100;

int energy_levels[HEIGHT][WIDTH] = {0};
int last_flush[HEIGHT][WIDTH] = {0};
int flush_count = 0;

void increase(int i, int j, int cur_step);

void flush(int i, int j, int cur_step) {
    last_flush[i][j] = cur_step;
    flush_count++;

    increase(i - 1, j, cur_step);
    increase(i - 1, j - 1, cur_step);
    increase(i - 1, j + 1, cur_step);
    increase(i, j - 1, cur_step);
    increase(i + 1, j - 1, cur_step);
    increase(i + 1, j, cur_step);
    increase(i + 1, j + 1, cur_step);
    increase(i, j + 1, cur_step);
}

void increase(int i, int j, int cur_step) {
    if (i < 0 || j < 0 || i >= HEIGHT || j >= WIDTH || last_flush[i][j] == cur_step) {
        return;
    }

    if (!(energy_levels[i][j] = (energy_levels[i][j] + 1) % 10)) {
        flush(i, j, cur_step);
    }
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    int i = 0;
    while (std::getline(fin, line)) {
        int j = 0;

        for (const char &energy_level: line) {
            energy_levels[i][j] = energy_level - '0';

            j++;
        }

        i++;
    }

    for (int s = 1; s <= STEPS; s++) {
        for (i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                increase(i, j, s);
            }
        }
    }


    std::cout << flush_count;

    return 0;
}
