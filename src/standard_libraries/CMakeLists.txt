
file(GLOB_RECURSE SOURCES "*.cpp")

file(GLOB_RECURSE HEADERS "*.hpp")

add_library(standard_library ${SOURCES} ${HEADERS})