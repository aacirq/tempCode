include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(ls ./ls/ls.cpp ./ls/list_file.cpp)
target_link_libraries(ls IncludeLib)

add_executable(ls2 ./ls/ls.c)
target_link_libraries(ls2 IncludeLib)
