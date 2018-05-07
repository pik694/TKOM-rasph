cmake_minimum_required(VERSION 3.10)
project(rasph)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.60 REQUIRED COMPONENTS unit_test_framework)

include_directories(src/)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src/lexer)
add_subdirectory(src/common)
add_subdirectory(src/parser)

add_subdirectory(tests)
add_subdirectory(tests/lexer_tests)
add_subdirectory(tests/parser_tests)