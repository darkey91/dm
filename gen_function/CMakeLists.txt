cmake_minimum_required(VERSION 3.8)
project(generating_function)

set(CMAKE_CXX_STANDARD 14)

add_executable(operation_1 operation_1.cpp)
add_executable(count_trees count_trees.cpp)
add_executable(operation_2 operation_2.cpp)
add_executable(construction construction.cpp)
add_executable(gen generator.cpp)
add_executable(trees trees_avoid_left_bruhes.cpp
)
