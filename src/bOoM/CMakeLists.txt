#source files to compile
set(stdBoOm_src
		aabr.cpp
		basemath.cpp
		color.cpp
		intersection.cpp
		math2d.cpp
		components/graphic.cpp
		entities/balloon/graphic.cpp
)

#build object files
add_library(boom ${stdBoOm_src})
