
file(GLOB_RECURSE SOURCES "*.cpp")

add_library(lexer ${SOURCES})
target_link_libraries(lexer common)
