cmake_minimum_required(VERSION 3.22)
project(day13_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(day13_2 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})