#include <iostream>
#include <fstream>
#include "string"
#include <map>
#include <set>

std::multimap<std::string, std::string> adjacency_matrix;
int path_count = 0;

void visit(std::string cave, std::set<std::string> visited) {
    if (cave == "end") {
        path_count++;
        return;
    }

    if (std::islower(cave.at(0))) {
        if (visited.contains(cave)) {
            return;
        }

        visited.insert(cave);
    }

    auto[begin, end] = adjacency_matrix.equal_range(cave);

    for (auto it = begin; it != end; ++it) {
        visit(it->second, visited);
    }
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    while (std::getline(fin, line)) {
        auto delimiter_pos = line.find('-');

        auto cave1 = line.substr(0, delimiter_pos);
        auto cave2 = line.substr(delimiter_pos + 1, line.size());

        adjacency_matrix.insert(std::pair<std::string, std::string>(cave1, cave2));
        adjacency_matrix.insert(std::pair<std::string, std::string>(cave2, cave1));
    }

    std::set<std::string> visited;

    visit("start", visited);

    std::cout << path_count;

    return 0;
}
