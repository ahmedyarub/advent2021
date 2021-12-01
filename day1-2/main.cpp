#include <iostream>
#include <fstream>
#include "string"

const int WINDOW_SIZE = 3;
const int BUFFER_SIZE = WINDOW_SIZE + 1;
int buffer[BUFFER_SIZE];
int buffer_pos = -1;

void insert(int val) {
    buffer_pos = (buffer_pos + 1) % BUFFER_SIZE;
    buffer[buffer_pos] = val;
}

int main() {
    std::string line;
    std::ifstream if_input("input.txt");
    int count = 0;

    for (int i = 0; i < WINDOW_SIZE; i++) {
        std::getline(if_input, line);

        insert(std::stoi(line));
    }

    while (std::getline(if_input, line)) {
        insert(std::stoi(line));

        int prev_pos;

        if ((prev_pos = buffer_pos - WINDOW_SIZE) < 0) {
            prev_pos = BUFFER_SIZE + prev_pos;
        }

        if (buffer[buffer_pos] > buffer[prev_pos]) {
            count++;
        }
    }

    std::cout << count;

    return 0;
}
