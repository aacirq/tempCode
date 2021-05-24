include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(cp ./cp/cp.c)
target_link_libraries(cp IncludeLib)

add_executable(who ./who/who.c ./who/utmplib.h)
target_link_libraries(who IncludeLib)
