cmake_minimum_required(VERSION 3.21)
project(cv03)

set(CMAKE_CXX_STANDARD 20)

add_executable(cv03 main.cpp vaccine.cpp vaccine.h child.cpp child.h date.cpp date.h)
