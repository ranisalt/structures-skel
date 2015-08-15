cmake_minimum_required(VERSION 3.2)
project(structures_skel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgtest -std=c++11")

add_subdirectory(arrays)
add_executable(unittest main_test.cpp)
target_link_libraries(unittest arrays_test)
