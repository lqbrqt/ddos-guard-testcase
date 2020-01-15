cmake_minimum_required(VERSION 3.15)
project(testcase)

set(CMAKE_CXX_STANDARD 14)

add_executable(testcase main.cpp)
TARGET_LINK_LIBRARIES(testcase readline json-c)