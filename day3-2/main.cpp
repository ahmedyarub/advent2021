#include <iostream>
#include <fstream>
#include "string"
#include <stack>

const int WORD_SIZE = 12;

int main() {
    std::string line;
    std::ifstream if_input("input.txt");
    auto *prev_oxygen_stack = new std::stack<std::string>();
    auto *prev_co2_stack = new std::stack<std::string>();

    while (std::getline(if_input, line)) {
        if (line.at(0) == '0') {
            prev_oxygen_stack->push(line);
        } else {
            prev_co2_stack->push(line);
        }
    }

    if (prev_co2_stack->size() > prev_oxygen_stack->size()) {
        auto *tmp = prev_oxygen_stack;
        prev_oxygen_stack = prev_co2_stack;
        prev_co2_stack = tmp;
    }

    std::string oxygen;
    auto *prev_stack = prev_oxygen_stack;

    for (int i = 1; i < WORD_SIZE; i++) {
        auto *next_zeros_stack = new std::stack<std::string>();
        auto *next_ones_stack = new std::stack<std::string>();

        while (!prev_stack->empty()) {
            if (prev_stack->top().at(i) == '0') {
                next_zeros_stack->push(prev_stack->top());
            } else {
                next_ones_stack->push(prev_stack->top());
            }

            prev_stack->pop();
        }

        prev_stack = next_zeros_stack->size() > next_ones_stack->size() ? next_zeros_stack : next_ones_stack;

        if (prev_stack->size() == 1) {
            oxygen = prev_stack->top();
            break;
        }
    }

    std::string co2;
    prev_stack = prev_co2_stack;

    for (int i = 1; i < WORD_SIZE; i++) {
        auto *next_zeros_stack = new std::stack<std::string>();
        auto *next_ones_stack = new std::stack<std::string>();

        while (!prev_stack->empty()) {
            if (prev_stack->top().at(i) == '0') {
                next_zeros_stack->push(prev_stack->top());
            } else {
                next_ones_stack->push(prev_stack->top());
            }

            prev_stack->pop();
        }

        prev_stack = next_zeros_stack->size() <= next_ones_stack->size() ? next_zeros_stack : next_ones_stack;

        if (prev_stack->size() == 1) {
            co2 = prev_stack->top();
            break;
        }
    }

    std::cout << std::stoi(oxygen, 0, 2) * std::stoi(co2, 0, 2);
    return 0;
}
