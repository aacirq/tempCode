include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_file_type test1_file_type.c)
target_link_libraries(test1_file_type IncludeLib)

add_executable(test2_access test2_access.c)
target_link_libraries(test2_access IncludeLib)

add_executable(test3_umask test3_umask.c)
target_link_libraries(test3_umask IncludeLib)

add_executable(test4_chmod test4_chmod.c)
target_link_libraries(test4_chmod IncludeLib)
