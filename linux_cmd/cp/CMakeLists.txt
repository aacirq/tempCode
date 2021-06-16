include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(cp ./cp.c)
target_link_libraries(cp IncludeLib)
