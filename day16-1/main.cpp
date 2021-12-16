#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

struct packet {
    int version;
    int value;
    std::vector<packet> sub_packets;

    packet(int version, int value, std::vector<packet> sub_ps) :
            version(version), value(value), sub_packets(std::move(sub_ps)) {};
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

int bin_to_dec(const std::string &s) {
    int i = 0;
    for (const char c: s) {
        i = i * 2 + (c - '0');
    }
    return i;
}

packet create_packet(const std::string &s, int &index) {
    const int version = bin_to_dec(s.substr(index, 3));
    index += 3;
    const int type = bin_to_dec(s.substr(index, 3));
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

        return {version, bin_to_dec(bin_num), std::vector<packet>()};
    } else {
        const int length_id = bin_to_dec(s.substr(index, 1));
        index += 1;

        if (length_id == 0) {
            const auto l_bits = bin_to_dec(s.substr(index, 15));

            index += 15;

            const auto init_index = index;
            auto p = packet(version, -1, std::vector<packet>());
            while (index < init_index + l_bits) {
                p.sub_packets.emplace_back(create_packet(s, index));
            }

            return p;
        } else if (length_id == 1) {
            const auto subpackets_count = bin_to_dec(s.substr(index, 11));

            index += 11;

            auto p = packet(version, -1, std::vector<packet>());
            for (int i = 0; i < subpackets_count; i++) {
                p.sub_packets.emplace_back(create_packet(s, index));
            }

            return p;
        }
    }
    return {0, 0, {}};
}

int versions_total(const packet &p) {
    int version = p.version;

    if (p.value == -1) {
        for (const auto &sub_packet: p.sub_packets) {
            version += versions_total(sub_packet);
        }
    }

    return version;
}

int main() {
    std::string line;
    std::fstream file("input.txt");

    std::getline(file, line);

    const auto b = hex_to_bin(line);
    int index = 0;
    auto p = create_packet(b, index);
    std::cout << versions_total(p);

    return 0;
}