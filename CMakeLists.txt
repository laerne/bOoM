cmake_minimum_required(VERSION 2.6)
project(bOoM)

# version number
set( bOoM_VERSION_MAJOR 0 )
set( bOoM_VERSION_MINOR 0 )
set( bOoM_VERSION_PATCH 0 )

# Set verbose
#set (CMAKE_VERBOSE_MAKEFILE true)

# Set environment
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pedantic -Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
include_directories("${CMAKE_SOURCE_DIR}/src")


# Build library, tests, ...
add_subdirectory(src/bOoM)
get_property(libboom_path TARGET boom PROPERTY location)

enable_testing()
add_subdirectory(src/test)

add_subdirectory(src/visualizer)
