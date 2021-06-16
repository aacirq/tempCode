include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(ls ls.cpp list_file.cpp)
target_link_libraries(ls IncludeLib)

add_executable(ls2 ls.c)
target_link_libraries(ls2 IncludeLib)
