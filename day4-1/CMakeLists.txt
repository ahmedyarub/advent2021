cmake_minimum_required(VERSION 3.22)
project(day4_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(day4_1 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})