#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string line;
    std::fstream file("input.txt");

    std::getline(file, line);

    auto y_pos = line.find('y') + 2;
    auto y_val = std::stoi(line.substr(y_pos, line.find("..", y_pos) - y_pos));

    int total = 0;

    for (int i = 1; i < std::abs(-1 * y_val); i++) {
        total += i;
    }

    std::cout << total;

    return 0;
}