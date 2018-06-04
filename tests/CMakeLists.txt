file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(all_tests ${SOURCES} )

target_include_directories(all_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(all_tests ${Boost_LIBRARIES} parser lexer interpreter common)