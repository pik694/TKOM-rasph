
find_package(Boost 1.60 REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})


add_subdirectory(./lexer_tests)