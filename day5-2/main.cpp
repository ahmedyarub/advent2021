#include <iostream>
#include <fstream>
#include "string"
#include <vector>
#include <sstream>
#include <map>
#include <array>
#include <numeric>
#include <set>

const int MAX_WIDTH = 1000;

struct point {
    int x;
    int y;

    point(int x, int y) : x(x), y(y) {}
};

struct segment {
    point from;
    point to;
    double slope;

    segment(point from, point to) : from(from),
                                    to(to),
                                    slope((double) (to.y - from.y) / (to.x - from.x)) {}
};

point coordinates_to_point(const std::string &coordinates) {
    auto delimiter_pos = coordinates.find(',');

    return {stoi(coordinates.substr(0, delimiter_pos)),
            stoi(coordinates.substr(delimiter_pos + 1, coordinates.size()))};
}

std::vector<segment> read_segments() {
    std::fstream fin("input.txt", std::fstream::in);
    std::string line;

    auto segs = std::vector<segment>();

    while (std::getline(fin, line)) {
        auto delimiter_pos = line.find(" -> ");

        auto p1 = coordinates_to_point(line.substr(0, delimiter_pos));
        auto p2 = coordinates_to_point(line.substr(delimiter_pos + 4, line.size()));

        if (p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y)) {
            segs.emplace_back(p1, p2);
        } else {
            segs.emplace_back(p2, p1);
        }
    }

    return segs;
}

int find_total_intersections(const std::vector<segment>& segments) {
    std::set<int> unique_points;
    std::set<int> unique_intersections;

    for (const auto &segment: segments) {
        if (segment.slope == 0) {
            for (int x = segment.from.x; x <= segment.to.x; x++) {
                auto key = segment.from.y * MAX_WIDTH + x;

                if (unique_points.contains(key)) {
                    unique_intersections.insert(key);
                } else {
                    unique_points.insert(key);
                }
            }
        } else if (segment.slope == std::numeric_limits<double>::infinity()) {
            for (int y = segment.from.y; y <= segment.to.y; y++) {
                auto key = y * MAX_WIDTH + segment.from.x;

                if (unique_points.contains(key)) {
                    unique_intersections.insert(key);
                } else {
                    unique_points.insert(key);
                }
            }
        } else if (segment.slope == 1) {
            for (int step = 0; step <= segment.to.x - segment.from.x; step++) {
                auto key = (segment.from.y + step) * MAX_WIDTH + segment.from.x + step;

                if (unique_points.contains(key)) {
                    unique_intersections.insert(key);
                } else {
                    unique_points.insert(key);
                }
            }
        } else if (segment.slope == -1) {
            for (int step = 0; step <= segment.to.x - segment.from.x; step++) {
                auto key = (segment.from.y - step) * MAX_WIDTH + segment.from.x + step;

                if (unique_points.contains(key)) {
                    unique_intersections.insert(key);
                } else {
                    unique_points.insert(key);
                }
            }
        }
    }

    return (int) unique_intersections.size();
}

int main() {
    auto segments = read_segments();

    std::cout << find_total_intersections(segments);
    return 0;
}
