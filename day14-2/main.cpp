#include <iostream>
#include <fstream>
#include "string"
#include <map>

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line, templ;
    std::map<std::string, std::string> pol_map;
    std::map<std::string, long long int> count_map;
    std::map<char, long long int> letter_count_map;

    std::getline(fin, templ);

    std::getline(fin, line);

    while (std::getline(fin, line)) {
        auto delimiter_pos = line.find(" -> ");

        auto key = line.substr(0, delimiter_pos);
        auto value = line.substr(delimiter_pos + 4, line.size());

        pol_map.try_emplace(key, value);
        count_map.try_emplace(key, 0);
        letter_count_map.emplace(key.at(0), 0);
        letter_count_map.emplace(key.at(1), 0);
    }

    for (int chr = 0; chr < templ.size() - 1; chr++) {
        count_map.at(templ.substr(chr, 2))++;
    }

    for (int s = 0; s < 40; s++) {
        std::map<std::string, long long int> next_count_map;

        for (const auto &count_pair: count_map) {
            auto insertion = pol_map.at(count_pair.first);
            auto first_pol = count_pair.first.substr(0, 1) + insertion;
            auto second_pol = insertion + count_pair.first.substr(1, 1);

            next_count_map[first_pol] += count_pair.second;
            next_count_map[second_pol] += count_pair.second;

        }

        count_map = std::move(next_count_map);
    }

    for (const auto &count_pair: count_map) {
        letter_count_map.at(count_pair.first.at(0)) += count_pair.second;
    }

    letter_count_map.at(templ.at(templ.size() - 1))++;

    long long int max = 0;
    long long int min = LLONG_MAX;

    for (const auto &letter_count: letter_count_map) {
        if(letter_count.second > max){
            max = letter_count.second;
        }

        if(letter_count.second < min){
            min = letter_count.second;
        }
    }

    std::cout << max - min;

    return 0;
}
