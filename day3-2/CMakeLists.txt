cmake_minimum_required(VERSION 3.22)
project(day3_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(day3_2 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})