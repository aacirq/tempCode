# include_directories(${PROJECT_SOURCE_DIR}/include)
cmake_minimum_required(VERSION 3.10)
project(linux_cmd)

add_subdirectory(./cp)
add_subdirectory(./ls)
add_subdirectory(./pwd)
add_subdirectory(./who)
add_subdirectory(./sh)

set(CMAKE_CXX_STANDARD 11)
