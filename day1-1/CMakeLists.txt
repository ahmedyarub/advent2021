cmake_minimum_required(VERSION 3.22)
project(day1_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(day1_1 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})