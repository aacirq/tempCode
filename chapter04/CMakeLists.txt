include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_file_type test1_file_type.c)
target_link_libraries(test1_file_type IncludeLib)
