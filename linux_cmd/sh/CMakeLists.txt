cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sh ./main.c ./sh.c ./sh.h varlib.h varlib.c)

