include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_stdio test1_stdio.c)
target_link_libraries(test1_stdio IncludeLib)
