cmake_minimum_required(VERSION 3.23)
project(Project2_Refactor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project2_Refactor main.cpp AdjacencyList.h test-unit/test.cpp test-unit/catch.hpp)
