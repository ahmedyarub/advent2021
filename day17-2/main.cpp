#include <iostream>
#include <fstream>
#include <string>

int main() {
    // read file
    std::string line;
    std::fstream file("input.txt");

    std::getline(file, line);

    auto x1_val = std::stoi(line.substr(15, line.find("..") - 15));
    auto x2_val = std::stoi(line.substr(line.find("..") + 2, line.find(',') - line.find("..") - 2));

    auto y_pos = line.find('y') + 2;
    auto y1_val = std::stoi(line.substr(y_pos, line.find("..", y_pos) - y_pos));
    auto y2_val = std::stoi(
            line.substr(line.find("..", y_pos) + 2, line.size() - line.find("..", y_pos) + 2));

    //find minimum horizontal velocity
    int min_x_vel = 0;
    int x_pos = x1_val;
    while (x_pos > 0) {
        min_x_vel++;

        x_pos -= min_x_vel;
    }
    min_x_vel--;

    // count starting velocities
    int count = 0;

    for (int x = min_x_vel; x <= x2_val; x++) {
        for (int y = -1 * abs(y1_val); y <= abs(y1_val); y++) {
            int cur_x = 0;
            int cur_y = 0;
            int vel_x = x;
            int vel_y = y;

            while (cur_x <= x2_val && cur_y >= y1_val) {
                cur_x += vel_x;

                if (vel_x > 0) {
                    vel_x--;
                }

                cur_y += vel_y;
                vel_y--;

                if (cur_x >= x1_val && cur_x <= x2_val &&
                    cur_y <= y2_val && cur_y >= y1_val) {
                    count++;
                    break;
                }
            }
        }
    }

    std::cout << count;

    return 0;
}