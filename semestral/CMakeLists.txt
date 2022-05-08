cmake_minimum_required(VERSION 3.21)
project(ts_paint)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")

add_executable(ts_paint
        main.cpp)
