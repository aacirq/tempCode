include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(who who.c utmplib.h)
target_link_libraries(who IncludeLib)
