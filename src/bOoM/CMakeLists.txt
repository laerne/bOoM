#source files to compile
set(stdBoOm_src
		aabr.cpp
		basemath.cpp
		color.cpp
		intersection.cpp
		math2d.cpp
)

#build object files
add_library(bOoM ${stdBoOm_src})
