#source files to compile
set(stdBoOm_src stdBoOm/basemath.cpp stdBoOm/intersection.cpp stdBoOm/math2d.cpp)

#build object files
add_library(boom ${stdBoOm_src})

#use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0")

message(STATUS ${CMAKE_SOURCE_DIR})
