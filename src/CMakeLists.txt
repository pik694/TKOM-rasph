
add_executable(main main.cpp)

target_include_directories(main PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(main ${Boost_LIBRARIES} parser lexer interpreter common)