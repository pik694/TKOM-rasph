cmake_minimum_required(VERSION 3.10)
project(rasph)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.60.0)

#include_directories(${Boost_INCLUDE_DIRS})

include_directories(./src/)

add_subdirectory(src/lexer)

add_subdirectory(tests)
