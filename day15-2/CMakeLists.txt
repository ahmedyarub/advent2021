cmake_minimum_required(VERSION 3.21.1)
project(day15_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(day15_2 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})