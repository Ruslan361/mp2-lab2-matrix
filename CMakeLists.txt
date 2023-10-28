cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME} LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})


add_executable(sample_matrix "./samples/sample_matrix.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/include/tmatrix.h"
"${CMAKE_CURRENT_SOURCE_DIR}/include/tdynamicvector.h")
#"${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest.h")
add_executable(${PROJECT_NAME}_test "./test/test_main.cpp" 
"./test/test_tmatrix.cpp" 
"./test/test_tvector.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/include/tmatrix.h")

set(TEST_NAME ${PROJECT_NAME}_test)
add_library(gtest "${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc" "${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest.h")
target_link_libraries(${TEST_NAME} PUBLIC gtest)
target_include_directories(sample_matrix PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${TEST_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/gtest" "${CMAKE_CURRENT_SOURCE_DIR}/include")