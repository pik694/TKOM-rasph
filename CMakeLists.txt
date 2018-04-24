cmake_minimum_required(VERSION 3.10)
project(rasph)

set(CMAKE_CXX_STANDARD 17)


include_directories(./src/)


add_subdirectory(src/lexer)



add_subdirectory(tests)
