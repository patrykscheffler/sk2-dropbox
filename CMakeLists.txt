cmake_minimum_required(VERSION 3.6)
project(sk2_dropbox)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main_server.c server/source/socket_err_check.c server/header/socket_err_check.h server/header/global_data.h
        server/source/socket_io.c server/header/socket_io.h server/source/client.c server/header/client.h
        server/source/server.c server/header/server.h)

find_package(Threads REQUIRED)
add_executable(sk2_dropbox ${SOURCE_FILES} main_server.c)
target_link_libraries(sk2_dropbox Threads::Threads)