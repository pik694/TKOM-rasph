file(GLOB_RECURSE SOURCES "*.cpp")

add_library(parser ${SOURCES})
target_link_libraries(parser lexer common)