cmake_minimum_required(VERSION 2.6)
project(bOoM)

# version number
set( bOoM_VERSION_MAJOR 0 )
set( bOoM_VERSION_MINOR 0 )
set( bOoM_VERSION_PATCH 0 )

# Set verbose
#set (CMAKE_VERBOSE_MAKEFILE true)

# Set environment
# Include files are not yet separated from source.
include_directories(${CMAKE_SOURCE_DIR}/src)

# Build library, tests, ...
add_subdirectory(src/bOoM)
enable_testing()
add_subdirectory(src/test)
add_subdirectory(src/visualizer)
