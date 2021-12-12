cmake_minimum_required(VERSION 3.22)
project(day12_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(day12_1 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})