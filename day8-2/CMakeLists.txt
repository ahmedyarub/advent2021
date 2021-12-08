cmake_minimum_required(VERSION 3.22)
project(day8_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(day8_2 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})