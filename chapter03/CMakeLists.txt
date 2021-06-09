include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_lseek test1_lseek.c)
target_link_libraries(test1_lseek IncludeLib)

add_executable(test2_file_hole test2_file_hole.c)
target_link_libraries(test2_file_hole IncludeLib)

add_executable(test3_cp test3_cp.c)
target_link_libraries(test3_cp IncludeLib)

add_executable(test4_fcntl test4_fcntl.c)
target_link_libraries(test4_fcntl IncludeLib)

add_executable(test2_O_APPEND test2_O_APPEND.c)
target_link_libraries(test2_O_APPEND IncludeLib)
