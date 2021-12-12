cmake_minimum_required(VERSION 3.22)
project(day11_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(day11_2 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})