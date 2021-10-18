include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(conf conf.c)
target_link_libraries(conf IncludeLib)
