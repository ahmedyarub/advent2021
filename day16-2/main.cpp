#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

struct Packet {
    long int type;
    long long value;
    std::vector<Packet> sub_ps;

    Packet(long int type, const long long value, std::vector<Packet> sub_ps) :
            type(type), value(value), sub_ps(std::move(sub_ps)) {};
};

std::string hex_to_bin(const std::string &s) {
    std::string r;

    for (char c: s) {
        unsigned int myval;
        std::stringstream ss;

        ss << c;
        ss >> std::hex >> myval;

        r += std::bitset<4>{myval}.to_string();
    }

    return r;
}

long int bin_to_dec(const std::string &s) {
    long int i = 0;

    for (const char c: s) {
        i = i * 2 + (c - '0');
    }

    return i;
}

long long packet_value(Packet &p) {
    if (p.value == -1) {
        for (auto &sub_p: p.sub_ps) {
            packet_value(sub_p);
        }
        if (p.type == 0) {
            p.value = 0;
            for (const auto &sub_p: p.sub_ps) {
                p.value += sub_p.value;
            }
        } else if (p.type == 1) {
            p.value = 1;
            for (const auto &sub_p: p.sub_ps) {
                p.value *= sub_p.value;
            }
        } else if (p.type == 2) {
            p.value = std::numeric_limits<long long>::max();
            for (const auto &sub_p: p.sub_ps) {
                p.value = std::min(p.value, sub_p.value);
            }
        } else if (p.type == 3) {
            p.value = std::numeric_limits<long long>::min();
            for (const auto &sub_p: p.sub_ps) {
                p.value = std::max(p.value, sub_p.value);
            }
        } else if (p.type == 5) {
            p.value = p.sub_ps[0].value > p.sub_ps[1].value ? 1 : 0;
        } else if (p.type == 6) {
            p.value = p.sub_ps[0].value < p.sub_ps[1].value ? 1 : 0;
        } else if (p.type == 7) {
            p.value = p.sub_ps[0].value == p.sub_ps[1].value ? 1 : 0;
        }
    }

    return p.value;
}

Packet create_packet(const std::string &s, size_t &index) {
    index += 3;
    long int type = bin_to_dec(s.substr(index, 3));
    index += 3;
    if (type == 4) {
        std::string bin_num;
        while (index < s.size()) {
            if (s[index] == '1') {
                bin_num += s.substr(index + 1, 4);
                index += 5;
            } else if (s[index] == '0') {
                bin_num += s.substr(index + 1, 4);
                index += 5;
                break;
            }
        }
        return {type, bin_to_dec(bin_num), std::vector<Packet>()};
    } else {
        long int length_id = bin_to_dec(s.substr(index, 1));
        index += 1;
        if (length_id == 0) {
            const auto l_bits = bin_to_dec(s.substr(index, 15));
            index += 15;
            const auto init_index = index;
            auto p = Packet(type, -1, std::vector<Packet>());
            while (index < init_index + l_bits) {
                p.sub_ps.emplace_back(create_packet(s, index));
            }
            return p;
        } else if (length_id == 1) {
            const auto n_sub_ps = bin_to_dec(s.substr(index, 11));
            index += 11;
            auto p = Packet(type, -1, std::vector<Packet>());
            for (int i = 0; i < n_sub_ps; i++) {
                p.sub_ps.emplace_back(create_packet(s, index));
            }
            return p;
        }
    }
}

int main() {
    std::string line;
    std::fstream file("input.txt");

    std::getline(file, line);

    const auto b = hex_to_bin(line);
    size_t index = 0;
    auto p = create_packet(b, index);
    std::cout << packet_value(p) << '\n';
    return 0;
}