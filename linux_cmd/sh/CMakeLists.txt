include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sh ./sh.c)
target_link_libraries(sh IncludeLib)
