cmake_minimum_required(VERSION 3.6)
project(c_parallel_sum)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(c_parallel_sum ${SOURCE_FILES})