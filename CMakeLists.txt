cmake_minimum_required(VERSION 3.10)
project(rasph)

set(CMAKE_CXX_STANDARD 17)


include_directories(./src/)

enable_testing()

add_subdirectory(src/lexer)
add_subdirectory(src/common)

add_subdirectory(tests)
