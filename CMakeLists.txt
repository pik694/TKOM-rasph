cmake_minimum_required(VERSION 3.11)
project(rasph)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.66.0 REQUIRED COMPONENTS program_options system unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src/lexer)

add_subdirectory(tests)