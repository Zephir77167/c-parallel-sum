cmake_minimum_required(VERSION 3.6)
project(c_parallel_sum)

set(CMAKE_C_STANDARD 99)
set(COMMON_C_FLAGS "-ansi -pedantic -Wall -Werror")


set(CMAKE_C_FLAGS COMMON_C_FLAGS)
set(SOURCE_FILES_SEQUENTIAL sequential/main.c)
add_executable(c_parallel_sum_sequential ${SOURCE_FILES_SEQUENTIAL})

set(CMAKE_C_FLAGS "-fopenmp ${COMMON_C_FLAGS}")
set(SOURCE_FILES_OPEN_MP open-mp/main.c)
add_executable(c_parallel_sum_open_mp ${SOURCE_FILES_OPEN_MP})

#set(CMAKE_C_FLAGS "-lOpenCL ${COMMON_C_FLAGS}")
#set(SOURCE_FILES_OPEN_CL open-cl/main.c)
#add_executable(c_parallel_sum_open_cl ${SOURCE_FILES_OPEN_CL})
