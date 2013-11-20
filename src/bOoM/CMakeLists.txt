#source files to compile
set(stdBoOm_src stdBoOm/basemath.cpp stdBoOm/intersection.cpp stdBoOm/math2d.cpp entities/world_boundary/WorldBoundary.cpp)

#build object files
add_library(boom ${stdBoOm_src})
