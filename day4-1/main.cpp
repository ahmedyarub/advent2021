#include <iostream>
#include <fstream>
#include "string"
#include <vector>
#include <sstream>
#include <map>
#include <array>
#include <numeric>

const int DIMENSION = 5;

class bingo_board {
    std::map<int, std::pair<int, int>> number_to_pos; // number -> row,col

    std::array<int, DIMENSION> marked_row;
    std::array<int, DIMENSION> marked_col;

    int calculate_remaining() {
        return std::accumulate(number_to_pos.begin(), number_to_pos.end(), 0,
                               [](int sum, auto num_pos) {
                                   return sum + num_pos.first;
                               });
    }

public:
    void add(int val, int row, int col) {
        number_to_pos.insert(std::pair<int, std::pair<int, int>>(val, std::pair<int, int>(row, col)));
    }

    int mark(int val) {
        auto[row, col] = number_to_pos.find(val)->second;
        number_to_pos.erase(val);

        if (++marked_row.at(row) == DIMENSION) {
            return calculate_remaining() * val;
        }

        if (++marked_col.at(col) == DIMENSION) {
            return calculate_remaining() * val;
        }

        return false;
    }
};

std::multimap<int, bingo_board *> number_to_board;

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;
    std::getline(fin, line);

    std::vector<int> draws;

    {
        std::stringstream ss(line);
        std::string substr;

        while (getline(ss, substr, ',')) {
            draws.push_back(std::stoi(substr));
        }
    }

    while (std::getline(fin, line)) {
        auto *cur_board = new bingo_board();

        for (int row = 0; row < DIMENSION; row++) {
            int col = 0;

            std::getline(fin, line);
            std::stringstream ss(line);

            std::string substr;
            while (getline(ss, substr, ' ')) {
                if (!substr.empty()) {
                    auto val = std::stoi(substr);
                    cur_board->add(val, row, col);
                    number_to_board.insert(std::pair<int, bingo_board *>(val, cur_board));

                    col++;
                }
            }
        }
    }

    for (auto draw: draws) {
        auto[begin, end] = number_to_board.equal_range(draw);

        for (auto it = begin; it != end; ++it) {
            auto mark_result = it->second->mark(draw);

            if (mark_result) {
                std::cout << mark_result;

                return 0;
            }
        }
    }

    return -1;
}
