cmake_minimum_required(VERSION 2.6)
project(bOoM)

#version number
set (bOoM_VERSION_MAJOR 0)
set (bOoM_VERSION_MINOR 0)

add_executable(boom_test main.cpp math2d.hpp dynamic.hpp)
target_link_libraries (boom_test m)
