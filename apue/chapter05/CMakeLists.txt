include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test1_get_put_char test1_get_put_char.c)
target_link_libraries(test1_get_put_char IncludeLib)

add_executable(test2_buffer_status test2_buffer_status.c)
target_link_libraries(test2_buffer_status IncludeLib)

add_executable(test3_tmpnam_tmpfile test3_tmpnam_tmpfile.c)
target_link_libraries(test3_tmpnam_tmpfile IncludeLib)

add_executable(test4_mkstemp test4_mkstemp.c)
target_link_libraries(test4_mkstemp IncludeLib)

add_executable(test5_memstream test5_memstream.c)
target_link_libraries(test5_memstream IncludeLib)

add_executable(test_buf_free test_buf_free.c)
