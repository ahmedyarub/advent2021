#include <iostream>
#include <fstream>
#include "string"
#include <map>
#include <set>

std::multimap<std::string, std::string> adjacency_matrix;
int path_count = 0;

void visit(std::string cave, std::set<std::string> visited, bool twice_visited) {
    if (cave == "end") {
        path_count++;
        return;
    }

    if (std::islower(cave.at(0))) {
        if (visited.contains(cave)) {
            if (twice_visited) {
                return;
            }

            twice_visited = true;
        } else {
            visited.insert(cave);
        }
    }

    auto[begin, end] = adjacency_matrix.equal_range(cave);

    for (auto it = begin; it != end; ++it) {
        visit(it->second, visited, twice_visited);
    }
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    while (std::getline(fin, line)) {
        auto delimiter_pos = line.find('-');

        auto cave1 = line.substr(0, delimiter_pos);
        auto cave2 = line.substr(delimiter_pos + 1, line.size());

        if (cave2 != "start" && cave1 != "end") {
            adjacency_matrix.insert(std::pair<std::string, std::string>(cave1, cave2));
        }

        if (cave1 != "start" && cave2 != "end") {
            adjacency_matrix.insert(std::pair<std::string, std::string>(cave2, cave1));
        }
    }

    std::set<std::string> visited;

    visit("start", visited, false);

    std::cout << path_count;

    return 0;
}
