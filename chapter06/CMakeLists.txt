include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_stdio test1_stdio.c)
target_link_libraries(test1_stdio IncludeLib)

add_executable(test2_read_line test2_read_line.c)
target_link_libraries(test2_read_line IncludeLib)
