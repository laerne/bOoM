#source files to compile
set(boomlib_src basemath.cpp intersection.cpp math2d.cpp)

#build object files
add_library(boom ${boomlib_src})

#use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0")

message(STATUS ${CMAKE_SOURCE_DIR})
