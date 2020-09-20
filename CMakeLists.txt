cmake_minimum_required(VERSION 2.8)
project(structures_skel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR} ${GTEST_INCLUDE_DIRS})

set(SRC_FILES main_test.cpp)
#add_subdirectory(arrays)
add_subdirectory(graphs)
add_subdirectory(linked)
add_executable(unittest ${SRC_FILES})
target_link_libraries(unittest ${CMAKE_THREAD_LIBS_INIT} ${GTEST_BOTH_LIBRARIES})
