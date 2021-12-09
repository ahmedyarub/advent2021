#include <iostream>
#include <fstream>
#include "string"

const int WIDTH = 100;
const int HEIGHT = 100;

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    int heights[HEIGHT][WIDTH];

    int i = 0;
    while (std::getline(fin, line)) {
        int j = 0;

        for (const char &height: line) {
            heights[i][j] = height - '0';

            j++;
        }

        i++;
    }

    int total = 0;
    for (i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (
                    ((i == 0) || (heights[i - 1][j] > heights[i][j])) &&            // up
                    ((j == WIDTH - 1) || (heights[i][j + 1] > heights[i][j])) &&    // right
                    ((i == HEIGHT - 1) || (heights[i + 1][j] > heights[i][j])) &&   // down
                    ((j == 0) || (heights[i][j - 1] > heights[i][j]))               // left
                    ) {
                std::cout << "i: " << i << " j: " << j << "\n";
                total += heights[i][j] + 1;
            }
        }
    }

    std::cout << total;

    return 0;
}
