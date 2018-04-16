cmake_minimum_required(VERSION 3.9)
project(rasph)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.66.0 REQUIRED COMPONENTS program_options filesystem system)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(rasph main.cpp)
    target_link_libraries(rasph ${Boost_LIBRARIES})
endif ()