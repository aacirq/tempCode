include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(myls myls.c)
target_link_libraries(myls IncludeLib)

add_executable(mycp mycp.c)
target_link_libraries(mycp IncludeLib)

add_executable(mycp_std mycp_std.c)
target_link_libraries(mycp_std IncludeLib)

add_executable(getpid getpid.c)
target_link_libraries(getpid IncludeLib)

add_executable(simshell simshell.c)
target_link_libraries(simshell IncludeLib)

add_executable(use_errno use_errno.c)
target_link_libraries(use_errno IncludeLib)

add_executable(getid getid.c)
target_link_libraries(getid IncludeLib)
