cmake_minimum_required(VERSION 3.6)
project(c_parallel_sum)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-fopenmp -ansi -pedantic -Wall -Werror")
set(SOURCE_FILES_OPEN_MP open-mp/main.c)
add_executable(c_parallel_sum_open_mp ${SOURCE_FILES_OPEN_MP})

#set(CMAKE_C_FLAGS "-lOpenCL -ansi -pedantic -Wall -Werror")
#set(SOURCE_FILES_OPEN_CL open-cl/main.c)
#add_executable(c_parallel_sum_open_cl ${SOURCE_FILES_OPEN_CL})
