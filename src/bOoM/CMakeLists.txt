#source files to compile
set(stdBoOm_src
		stdBoOm/aabr.cpp
		stdBoOm/basemath.cpp
		stdBoOm/color.cpp
		stdBoOm/intersection.cpp
		stdBoOm/math2d.cpp
		entities/Entity.cpp
		entities/world_boundary/WorldBoundary.cpp
		entities/balloon/Balloon.cpp
)

#build object files
add_library(boom ${stdBoOm_src})
