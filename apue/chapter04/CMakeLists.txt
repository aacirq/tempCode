include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_file_type test1_file_type.c)
target_link_libraries(test1_file_type IncludeLib)

add_executable(test2_access test2_access.c)
target_link_libraries(test2_access IncludeLib)

add_executable(test3_umask test3_umask.c)
target_link_libraries(test3_umask IncludeLib)

add_executable(test4_chmod test4_chmod.c)
target_link_libraries(test4_chmod IncludeLib)

add_executable(test5_unlink test5_unlink.c)
target_link_libraries(test5_unlink IncludeLib)

add_executable(test6_futimens test6_futimens.c)
target_link_libraries(test6_futimens IncludeLib)

add_executable(test7_getcwd test7_getcwd.c)
target_link_libraries(test7_getcwd IncludeLib)

add_executable(test8_st_dev test8_st_dev.c)
target_link_libraries(test8_st_dev IncludeLib)

add_executable(test9_traverse test9_traverse)
target_link_libraries(test9_traverse IncludeLib)
