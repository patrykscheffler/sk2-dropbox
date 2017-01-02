cmake_minimum_required(VERSION 3.6)
project(sk2_dropbox)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c)

find_package(Threads REQUIRED)
add_executable(sk2_dropbox ${SOURCE_FILES} main.c)
target_link_libraries(sk2_dropbox Threads::Threads)