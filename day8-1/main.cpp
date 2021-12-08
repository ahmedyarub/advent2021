#include <iostream>
#include <fstream>
#include "string"
#include <sstream>

int main() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    int total = 0;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string substr;

        bool save_digits = false;

        while (getline(ss, substr, ' ')) {
            if (substr == "|") {
                save_digits = true;
                continue;
            }

            if (save_digits) {
                int length = substr.length();

                if (length == 2 || length == 3 || length == 4 || length == 7) {
                    total++;
                }
            }
        }
    }

    std::cout << total;

    return 0;
}
