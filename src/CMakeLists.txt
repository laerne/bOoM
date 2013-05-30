project(bOoM)

# CMake version
cmake_minimum_required(VERSION 2.6)
# version number
set (bOoM_VERSION_MAJOR 0)
set (bOoM_VERSION_MINOR 0)

# Set verbose
#set (CMAKE_VERBOSE_MAKEFILE true)

# Build library, tests, ...
add_subdirectory(bOoM)
add_subdirectory(test)
