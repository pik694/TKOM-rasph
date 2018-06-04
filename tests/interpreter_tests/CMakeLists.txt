file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(interpreter_tests ../tests_main.cpp ${SOURCES} )

target_include_directories(interpreter_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(interpreter_tests ${Boost_LIBRARIES} standard_library interpreter common parser)