#include <iostream>
#include <fstream>
#include "string"
#include <map>

std::map<std::string, std::string> pol_map;

int getMaxOccuringChar(const std::string &str) {
    int count[256] = {0};

    int max = 0;

    for (int i = 0; i < str.length(); i++) {
        count[str[i]]++;
        if (max < count[str[i]]) {
            max = count[str[i]];
        }
    }

    int min = INT_MAX;
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0 && min > count[i]) {
            min = count[i];
        }
    }

    return max - min;
}


int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line, templ;

    std::getline(fin, templ);

    std::getline(fin, line);

    while (std::getline(fin, line)) {
        auto delimiter_pos = line.find(" -> ");

        auto key = line.substr(0, delimiter_pos);
        auto value = line.substr(delimiter_pos + 4, line.size());

        pol_map.try_emplace(key, value);
    }

    for (int s = 0; s < 10; s++) {
        std::string new_str{templ.at(0)};

        for (int chr = 0; chr < templ.size() - 1; chr++) {
            new_str.append(pol_map.at(templ.substr(chr, 2)));
            new_str.append(templ.substr(chr + 1, 1));
        }
        templ = std::move(new_str);
    }

    std::cout << getMaxOccuringChar(templ);

    return 0;
}
