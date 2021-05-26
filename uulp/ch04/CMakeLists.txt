include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(pwd ./pwd/pwd.cpp)
target_link_libraries(pwd IncludeLib)
