cmake_minimum_required(VERSION 3.15)
project(STL_examples)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES STL_examples.cpp)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR} /include ${gtest_SOURCE_DIR})
add_executable(STL_examples_test_run ${SOURCE_FILES})
target_link_libraries(STL_examples_test_run gtest gtest_main)