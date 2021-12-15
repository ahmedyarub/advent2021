cmake_minimum_required(VERSION 3.21.1)
project(day14_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(day14_1 main.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})