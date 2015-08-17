cmake_minimum_required(VERSION 2.8)
project(structures_skel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgtest -std=c++11")

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR})

set(SRC_FILES main_test.cpp)
add_subdirectory(arrays)
add_executable(unittest ${SRC_FILES})
