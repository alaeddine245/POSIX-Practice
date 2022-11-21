cmake_minimum_required(VERSION 3.23)
project(TP2_POSIX C)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(TP2_POSIX main.c)

target_link_libraries(TP2_POSIX PRIVATE Threads::Threads)
