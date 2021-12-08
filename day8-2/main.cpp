#include <iostream>
#include <fstream>
#include "string"
#include <sstream>
#include <array>
#include <map>
#include <algorithm>

bool has_segment(const std::string &word, char chr) {
    return word.find(chr) != std::string::npos;
}

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    std::array<std::string, 4> words;

    int total = 0;
    while (std::getline(fin, line)) {
        int j = 0;
        std::stringstream ss(line);
        std::string substr;
        std::map<int, std::string> length_to_word;
        bool save_digits = false;

        while (getline(ss, substr, ' ')) {
            if (substr == "|") {
                save_digits = true;
                continue;
            }

            if (save_digits) {
                words.at(j) = substr;
                j++;
            } else {
                length_to_word.try_emplace(substr.length(), substr);
            }
        }

        int cur_num = 0;

        for (const auto &word: words) {
            int digit = 0;

            switch (word.length()) {
                case 2:
                    digit = 1;
                    break;
                case 3:
                    digit = 7;
                    break;
                case 4:
                    digit = 4;
                    break;
                case 5: // 2,3,5
                    if (has_segment(word, length_to_word.at(2).at(0)) &&
                        has_segment(word, length_to_word.at(2).at(1))) {
                        digit = 3;
                    } else {
                        int count_common = 0;

                        for (auto cur_char: length_to_word.at(4)) {
                            if (has_segment(word, cur_char)) {
                                count_common++;
                            }
                        }

                        if (count_common == 2) {
                            digit = 2;
                        } else {
                            digit = 5;
                        }
                    }
                    break;
                case 6: // 0,6,9
                    if (!(has_segment(word, length_to_word.at(2).at(0)) &&
                          has_segment(word, length_to_word.at(2).at(1)))) {
                        digit = 6;
                    } else {
                        if (std::ranges::none_of(length_to_word.at(4),
                                                 [word](char chr) { return !has_segment(word, chr); })) {
                            digit = 9;
                        }
                    }

                    break;
                case 7:
                    digit = 8;
            }

            cur_num = cur_num * 10 + digit;
        }

        total += cur_num;
    }

    std::cout << total;

    return 0;
}
