cmake_minimum_required(VERSION 2.6)
project(bOoM)

#version number
set (bOoM_VERSION_MAJOR 0)
set (bOoM_VERSION_MINOR 0)

#define executable
add_executable(boom_test
        basemath.cpp
        basemath.hpp
        dynamic.hpp
        intersection.hpp
        main.cpp
        math2d.cpp
        math2d.hpp
        )
target_link_libraries (boom_test m)

#use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0")
