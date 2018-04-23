
file(GLOB_RECURSE SOURCES "*.cpp")

add_library(lexer STATIC ${SOURCES})

#add_executable(lexer ${SOURCES} ${HEADERS})
#target_link_libraries(lexer ${Boost_LIBRARIES})
