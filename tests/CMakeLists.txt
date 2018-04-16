
enable_testing()


add_executable(unit_tests lexer_tests/sample_tests.cpp)
link_libraries(unit_tests ${Boost_LIBRARIES})

