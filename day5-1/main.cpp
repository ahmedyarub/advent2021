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

        if (p1.x == p2.x) {
            if (p1.y < p2.y) {
                segs.emplace_back(p1, p2);
            } else {
                segs.emplace_back(p2, p1);
            }
        } else if (p1.y == p2.y) {
            if (p1.x < p2.x) {
                segs.emplace_back(p1, p2);
            } else {
                segs.emplace_back(p2, p1);
            }
        }
    }

    return segs;
}

std::vector<point> get_intersections(segment s1, segment s2) {
    std::vector<point> intersections;

    if (s1.slope == s2.slope) {
        if (s1.slope == 0 && s1.from.y == s2.from.y) {
            if (s2.from.x < s1.from.x) {
                segment temp = s1;
                s1 = s2;
                s2 = temp;
            }

            if (s1.to.x >= s2.from.x) {
                for (int x = s2.from.x; x <= std::min(s1.to.x, s2.to.x); x++) {
                    intersections.emplace_back(x, s1.from.y);
                }
            }
        } else if (s1.slope == std::numeric_limits<double>::infinity() && s1.from.x == s2.from.x) {
            if (s2.from.y < s1.from.y) {
                segment temp = s1;
                s1 = s2;
                s2 = temp;
            }

            if (s1.to.y >= s2.from.y) {
                for (int y = s2.from.y; y <= std::min(s1.to.y, s2.to.y); y++) {
                    intersections.emplace_back(s1.from.x, y);
                }
            }
        }
    } else {
        if (s2.slope == 0) {
            segment temp = s1;
            s1 = s2;
            s2 = temp;
        }

        if (s1.from.y >= s2.from.y && s1.from.y <= s2.to.y &&
            s2.from.x >= s1.from.x && s2.from.x <= s1.to.x) {
            intersections.emplace_back(s2.from.x, s1.from.y);
        }
    }

    return intersections;
}

int find_total_intersections(std::vector<segment> segments) {
    std::set<int> unique_intersections;

    for (int i = 0; i < segments.size() - 1; i++) {
        for (int j = i + 1; j < segments.size(); j++) {
            for (const auto &intersection_point: get_intersections(segments[i], segments[j])) {
                unique_intersections.insert(intersection_point.y * MAX_WIDTH + intersection_point.x);
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
