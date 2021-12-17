cmake_minimum_required(VERSION 3.22)
project(day17_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(day17_2 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})