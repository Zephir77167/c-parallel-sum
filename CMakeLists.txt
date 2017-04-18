cmake_minimum_required(VERSION 3.6)
project(c_parallel_sum)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-ansi -pedantic -Wall -Werror -O3 -march=native")
set(COMMON_UTILS_SOURCES utils/args.c utils/arrays.c utils/timers.c)

set(SOURCE_FILES_SEQUENTIAL ${COMMON_UTILS_SOURCES} sequential/main.c)
add_executable(c_parallel_sum_sequential ${SOURCE_FILES_SEQUENTIAL})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(SOURCE_FILES_OPEN_MP ${COMMON_UTILS_SOURCES} open-mp/main.c)
add_executable(c_parallel_sum_open_mp ${SOURCE_FILES_OPEN_MP})

set(OpenCL_LIBRARY OpenCL)
find_package(OpenCL REQUIRED)
link_directories(${OpenCL_LIBRARY})

set(SOURCE_FILES_OPEN_CL ${COMMON_UTILS_SOURCES} open-cl/main.c)
add_executable(c_parallel_sum_open_cl ${SOURCE_FILES_OPEN_CL})
target_include_directories (c_parallel_sum_open_cl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (c_parallel_sum_open_cl ${OpenCL_LIBRARY})
