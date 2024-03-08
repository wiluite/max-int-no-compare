cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)
project(project1)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(test test.cpp)
