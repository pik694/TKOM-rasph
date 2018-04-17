

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h*")

add_library(lexer STATIC ${SOURCES} ${HEADERS})
target_link_libraries(lexer ${Boost_LIBRARIES})
