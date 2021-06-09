include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_lseek test1_lseek.c)
target_link_libraries(test1_lseek IncludeLib)

add_executable(test2_file_hole test2_file_hole.c)
target_link_libraries(test2_file_hole IncludeLib)

add_executable(test2_O_APPEND test2_O_APPEND.c)
target_link_libraries(test2_O_APPEND IncludeLib)

add_executable(test3_cp test3_cp.c)
target_link_libraries(test3_cp IncludeLib)

add_executable(test3_offset_of_two_fd test3_offset_of_two_fd.c)
target_link_libraries(test3_offset_of_two_fd IncludeLib)

add_executable(test4_fcntl test4_fcntl.c)
target_link_libraries(test4_fcntl IncludeLib)

add_executable(test_exercise_3_2 test_exercise_3_2.cpp)
target_link_libraries(test_exercise_3_2 IncludeLib)

add_executable(test_exercise_3_6 test_exercise_3_6.c)
target_link_libraries(test_exercise_3_6 IncludeLib)
