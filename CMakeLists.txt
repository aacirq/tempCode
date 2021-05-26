cmake_minimum_required(VERSION 3.10)

project(testApue)

add_subdirectory(./include)
add_subdirectory(./chapter01)
add_subdirectory(./chapter02)
add_subdirectory(./chapter03)
add_subdirectory(./uulp/ch02)
add_subdirectory(./uulp/ch03)
add_subdirectory(./uulp/ch04)

set(CMAKE_CXX_STANDARD 11)

add_executable(testApue main.cpp)
